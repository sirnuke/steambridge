// callback.cpp - Handles callback API calls
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include <cstdio>

#include <dlfcn.h>

#include <steam_api.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <wine/debug.h>

#include "api.h"
#include "logging.h"
#include "state.h"

typedef void (*steam_api_RunCallbacks_t)(void);
typedef void (*steam_api_RegisterCallback_t)(class CCallbackBase *, int);
typedef void (*steam_api_UnregisterCallback_t)(class CCallbackBase *);

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

//class CallbackImpl : protected CCallbackBase
// TODO: It's unclear whether making the base public (over private
//       or protected in the steam headers) has any impact.  At the moment,
//       it doesn't seem like it should from libsteam_api.so's perspective.
//
class CallbackImpl : protected CCallbackBase
{
  public:
    CallbackImpl(steam_bridge_CallbackRunFunc run, 
        steam_bridge_CallbackRunArgsFunc runargs, void *cCallbackBase, int size);
    ~CallbackImpl();
    virtual void Run(void *pvParam);
    virtual void Run(void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall);
    virtual int GetCallbackSizeBytes();

  private:
    // Pointer to the win32 CCallbackBase object
    void *cCallbackBase;
    // Size of the callback structure
    int size;

    // Function pointers to the win32 location to run callbacks
    steam_bridge_CallbackRunFunc run;
    steam_bridge_CallbackRunArgsFunc runargs;

    friend int SteamAPI_RegisterCallback_(steam_bridge_CallbackRunFunc,
        steam_bridge_CallbackRunArgsFunc, void *, int, int);
    friend void SteamAPI_UnregisterCallback_(void *cCallbackBase);
};

CallbackImpl::CallbackImpl(steam_bridge_CallbackRunFunc run,
    steam_bridge_CallbackRunArgsFunc runargs, void *cCallbackBase, int size) 
  : CCallbackBase(), cCallbackBase(cCallbackBase), size(size), run(run), runargs(runargs)
{
  WINE_TRACE("(this=%p,%p,%p,%p,%i)\n", this, run, runargs, cCallbackBase,
      size);
  m_iCallback = 0;
  m_nCallbackFlags = 0;
}

CallbackImpl::~CallbackImpl()
{
  WINE_TRACE("(this=%p)\n", this);
}

// A now for a word or two on the Callback function pointers:
// 
// Real steam_api.dll uses a simple virtual function for the callbacks.
// This doesn't work across the Wine->Linux boundary.  Interestingly enough,
// the Win32 code running in Wine calls the correct Linux virtual function,
// but thiscall is considerably different between GCC and Visual Studio.
// Noticeably, Visual Studio uses callee cleanup and LTR (!) arguments, and GCC uses
// C-style caller and RTL arguments.  While the right function executes,
// the arguments are messed up and it's unlikely you'd be able to get the
// function to return correctly.
//
// This necessitates the two different SteamBridge DLLs, as the proxy
// DLL is compiled under Visual Studio and offers the wrapping C++ functions
// compiled in the same form as the real DLL, versus this bridge library that
// compiles classes in the GCC/Linux fashion for the Linux steam_api.so.
// For most functions, a wrapping C interface is fine, if slightly painful
// to write all the glue code.  However, there's isn't an easy way
// to call functions on the Wine side from the Winelib DLL.  Winelib DLLs
// are effectively entirely Linux code, and cannot link against Win32 DLLs.
// Fortunately, C-style calls are nearly identical on GCC/Linux and VS/Win32.
// At a glance of various Internet documents, it seems like returning
// values could be trouble, but arguments are handled in the same way.
// Note that GCC has a 16-byte stack alignment behavior that Visual Studio
// may or may not have.  Thanks to caller cleanup and the simple nature of
// the callback arguments (pointers, ints, and int64) this shouldn't cause
// any trouble either way.
//
// So in short, this callback method is an ugly, ugly, ugly, ugly method
// that depends heavily on somewhat coincidental behavior between Linux
// and Windows.  It's extremely brittle, and liable to break into a
// million pieces if you so much look at it the wrong way, or really think
// about it.


void CallbackImpl::Run(void *pvParam)
{
  WINE_TRACE("Starting callback from bridge... (this=%p,param=%p,func=%p)\n",
      this, pvParam, run);
  (*run)(cCallbackBase, m_nCallbackFlags, pvParam);
  WINE_TRACE("Finished callback in bridge... (this=%p,param=%p,func=%p)\n",
      this, pvParam, run);
}

void CallbackImpl::Run(void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall)
{
  WINE_TRACE("(this=%p,pvParam=%p,bIOFailure=%i,hSteamAPICall=%llu)\n",
      this, pvParam, bIOFailure, hSteamAPICall);
  WINE_TRACE("Starting callback+ from bridge... (this=%p,param=%p,func=%p)",
      this, pvParam, run);
  (*runargs)(cCallbackBase, m_nCallbackFlags, pvParam, bIOFailure, hSteamAPICall);
  WINE_TRACE("Finished callback+ in bridge... (this=%p,param=%p,func=%p)",
      this, pvParam, run);
}

int CallbackImpl::GetCallbackSizeBytes()
{
  // TODO: It's possible this value changes in a custom implementation
  //       of CCallbackBase, though as a wild guess this isn't used in pratice.
  //       The two (technically three) implementations in steam_api.h return
  //       sizeof on a class - which will be constant.
  //
  // TODO: Update, said class is one of the many callback structs that
  //       are used.  It's possible, but unlikely, that if a client
  //       reused a CCallbackBase object this could change.  Said
  //       developers should probably be slapped.  Nonetheless, it's
  //       worth at least catching and aborting in this behavior.
  //
  return size;
}

extern "C"
{

void SteamAPI_RunCallbacks_()
{
  // Note that this appears to be purely single threaded event checking.
  // All Run(...) executions occur while SteamAPI_RunCallbacks()
  // is executing.  It's possible (though unideal) to 'reque' all fired
  // callbacks and return the data in some form from this bridge function.
  // This may be necessary if calling the parent win32 proxy library via
  // function pointers isn't possible (see above notes/implementation about
  // cross-OS C-style function calls).
  __DLSYM_GET(steam_api_RunCallbacks_t, api, "SteamAPI_RunCallbacks");
  (*api)();
}

int SteamAPI_RegisterCallback_(steam_bridge_CallbackRunFunc run,
    steam_bridge_CallbackRunArgsFunc runargs, void *cCallbackBase, int callback, int size)
{
  WINE_TRACE("(%p,%p,%p,%i,%i)\n", run, runargs, cCallbackBase, callback, size);

  // TODO: If this object has already been Registered, we should catch
  //       and handle this.  If it's not unregistered, probably unregister
  //       it.  Unregistering is the ideal place to delete the wrapper,
  //       so we'll then recreate it here.

  if (!state)
  {
    WINE_ERR("Calling SteamAPI_InitSafe in RegisterCallback for the app\n");
    if (!SteamAPI_InitSafe_())
      __ABORT("InitSafe failed when called from RegisterCallback!");
  }

  // To make the behavior clear, flags is bits settings that track the
  // state of the callback.  There's only two: 0x1 records whether it's
  // registered, 0x2 records whether it's a game server callback (the exact
  // behavior of this isn't clear yet).  iCallback refers to the callback
  // number, and it's set by SteamAPI_RegisterCallback.  This corresponds to
  // one of the callback structs defined all over the place, which contain
  // a field call k_iCallback (==iCallback).  This is template 'class P',
  // and is passed as the first parameter in the two Run(...) functions.
  // GetCallbackSizeBytes returns the size of this callback struct.
  // Fortunately for us, as it's pure data there shouldn't be any need to
  // do any converting between Linux and Wine.

  CCallbackBase *reference = (CCallbackBase *)(cCallbackBase);
  CallbackImpl *wrapper = new CallbackImpl(run, runargs, reference, size);

  WINE_TRACE("Logging callback wrapper (%p,%i,%i)->(%p,callback=%i,flags=%i)\n", reference,
      callback, size, wrapper, wrapper->m_iCallback, wrapper->m_nCallbackFlags);

  state->addCallback(wrapper, reference);
  __DLSYM_GET(steam_api_RegisterCallback_t, api, "SteamAPI_RegisterCallback");
  (*api)(wrapper, callback);

  WINE_TRACE("Callback registered (wrapper=%p,base=%p,callback=%i,flags=%i)\n", wrapper, reference,
      wrapper->m_iCallback, wrapper->m_nCallbackFlags);

  if (wrapper->m_iCallback != callback)
    __ABORT("Callback doesn't match expected after RegisterCallback! "
        "(wrapper=%p,base=%p,expected=%i,actual=%i)", wrapper, reference, callback,
        wrapper->m_iCallback);

  return wrapper->m_nCallbackFlags;
}

STEAM_API_BRIDGE_API void SteamAPI_UnregisterCallback_(void *cCallbackBase)
{
  WINE_TRACE("(%p)\n", cCallbackBase);
  if (!state) __ABORT("NULL internal state");

  CCallbackBase *reference = (CCallbackBase *)(cCallbackBase);
  CallbackImpl *wrapper = reinterpret_cast<CallbackImpl *>(state->getCallback(reference));
  __DLSYM_GET(steam_api_UnregisterCallback_t, api, "SteamAPI_UnregisterCallback");
  // TODO: Flaggsss
  (*api)(wrapper);
  state->removeCallback(reference);
  // TODO: Research destructors, there's nothing defined by steam_api.h -
  //       so this probabbbllly works right, but G++ complains
  delete wrapper;
}

} // extern "C"

