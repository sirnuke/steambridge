// callback.cpp - Handles callback API calls

#include <cstdio>

#include <steam_api.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <wine/debug.h>

#include "api.h"
#include "core.h"
#include "logging.h"


WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

//class CallbackImpl : protected CCallbackBase
// TODO: It's unclear whether making the base public (over private
//       or protected in the steam headers) has any impact.  At the moment,
//       it doesn't seem like it should from libsteam_api.so's perspective.
//
class CallbackImpl : public CCallbackBase
{
  public:
    CallbackImpl(steam_bridge_CallbackRunFunc run, 
        steam_bridge_CallbackRunArgsFunc runargs, void *cCallbackBase, int size);
    //CCallbackBase() { m_nCallbackFlags = 0; m_iCallback = 0; }
    // don't add a virtual destructor because we export this binary interface across dll's
    virtual void Run(void *pvParam);
    virtual void Run(void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall);
    //int GetICallback() { return m_iCallback; }
    virtual int GetCallbackSizeBytes();
  private:
    void *cCallbackBase;
    int size;

    steam_bridge_CallbackRunFunc run;
    steam_bridge_CallbackRunArgsFunc runargs;
  //protected:
    //enum { k_ECallbackFlagsRegistered = 0x01, k_ECallbackFlagsGameServer = 0x02 };
    //uint8 m_nCallbackFlags;
    //int m_iCallback;
    //friend class CCallbackMgr;
    friend int steam_bridge_SteamAPI_RegisterCallback(
        steam_bridge_CallbackRunFunc, steam_bridge_CallbackRunArgsFunc,
        void *, int, int);
};

// A now for a word or two on the Callback function pointers:
// 
// Real steam_api.dll uses a simple virtual function for the callbacks.
// This doesn't work across the Wine->Linux boundary.  Interestingly enough,
// the Win32 code running in Wine calls the correct Linux virtual function,
// but thiscall is considerably different between GCC and Visual Studio.
// Noticeably, Visual Studio uses callee and LTR (!) arguments, and GCC uses
// C-style caller and RTL arguments.  While the right function executes,
// the arguments are messed up and it's unlikely you'd be able to get the
// function to return correctly.
//
// This necessitates the two different SteamBridge DLLs, as the proxy
// DLL is compiled under Visual Studio and offers the wrapping C++ functions
// compiled in the same form as the real DLL, versus this bridge library that
// compiles classes in the GCC/Linux fashion for the Linux steam_api.so.
// For most functions, a wrapping C interface is fine, if slightly painful
// to write all the glue code.  However, there's isn't a super logical way
// to call functions on the Wine side from the Winelib DLL.  Winelib DLLs
// are effectively entirely Linux code, and cannot link against Win32 DLLs.
// Fortunately, C-style calls are nearly identical on GCC/Linux and VS/Win32.
// At a glance of various Internet documents, it seems like returning
// values would be trouble, but arguments are handled in the same way.
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
//
// On a side note, despite the "this is as clean of a break from x86 as
// we'll get so lets fix a few annoying things like the lack of general
// purpose registers" nature of x86-64, the default conventions are still
// different in the magical 64-bit land.  Microsoft went with a stdcall
// style LTR argument order, but cdecl style caller cleanup.  GCC still
// uses cdecl.  Wheee...

CallbackImpl::CallbackImpl(steam_bridge_CallbackRunFunc run,
    steam_bridge_CallbackRunArgsFunc runargs, void *cCallbackBase, int size) 
  : CCallbackBase(), cCallbackBase(cCallbackBase), size(size), run(run), runargs(runargs)
{
}

void CallbackImpl::Run(void *pvParam)
{
  WINE_TRACE("(this=0x%p,pvParam=0x%p)", this, pvParam);
  (*run)(cCallbackBase, m_nCallbackFlags, pvParam);
}

void CallbackImpl::Run(void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall)
{
  WINE_TRACE("(this=0x%p,pvParam=0x%p,bIOFailure=%i,hSteamAPICall=%llu)", this, pvParam, bIOFailure, hSteamAPICall);
  (*runargs)(cCallbackBase, m_nCallbackFlags, pvParam, bIOFailure, hSteamAPICall);
}

int CallbackImpl::GetCallbackSizeBytes()
{
  // TODO: It's possible this value changes in a custom implementation
  //       of CCallbackBase, though as a wild guess this isn't used in pratice.
  //       The two (technically three) implementations in steam_api.h return
  //       sizeof on a class - which will be constant.
  return size;
}

extern "C"
{

void steam_bridge_SteamAPI_RunCallbacks()
{
  WINE_TRACE("()");
  SteamAPI_RunCallbacks();
}

int steam_bridge_SteamAPI_RegisterCallback(steam_bridge_CallbackRunFunc run, 
    steam_bridge_CallbackRunArgsFunc runargs, void *cCallbackBase, int callback, 
    int size)
{
  // TODO: Populate CallbackImpl with data?  (flags, iCallback?)
  WINE_TRACE("(0x%p,0x%p,0x%p,%i,%i)", run, runargs, cCallbackBase, callback, size);

  if (!context)
    __ABORT__("No context (Init not called, or failed)!");

  CallbackImpl *c = new CallbackImpl(run, runargs, cCallbackBase, size);
  __LOG_ARGS_MSG__("Logging wrapper for callback", "(0x%p,%i,%i)->(0x%p)", cCallbackBase, callback, size, c);
  // TODO: Is this right?  Maybe?
  c->m_iCallback = callback;
  context->addCallback(c);
  SteamAPI_RegisterCallback(c, callback);
  // TODO: We should probabllly store the object.  Memory leaks and all
  //       that.  However, it's probably a safe guess that apps rarely
  //       (if ever) change their callbacks.
  // TODO: Flags are probably being set after RegisterCallback.
  //       Should update the win32 side proxy (return it as a value?)
  return c->m_nCallbackFlags;
}

} // extern "C"


