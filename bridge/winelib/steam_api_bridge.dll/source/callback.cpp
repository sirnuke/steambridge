// callback.cpp - Handles callback API calls

#include <cstdio>

#include <steam_api.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <wine/debug.h>

#include "api.h"
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
    CallbackImpl(void *wrapper, int size);
    //CCallbackBase() { m_nCallbackFlags = 0; m_iCallback = 0; }
    // don't add a virtual destructor because we export this binary interface across dll's
    virtual void Run(void *pvParam);
    virtual void Run(void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall);
    //int GetICallback() { return m_iCallback; }
    virtual int GetCallbackSizeBytes();
  private:
    void *wrapper __attribute__ ((unused));
    int size;
  //protected:
    //enum { k_ECallbackFlagsRegistered = 0x01, k_ECallbackFlagsGameServer = 0x02 };
    //uint8 m_nCallbackFlags;
    //int m_iCallback;
    //friend class CCallbackMgr;
};

CallbackImpl::CallbackImpl(void *wrapper, int size) : CCallbackBase(), wrapper(wrapper), size(size)
{
}

void CallbackImpl::Run(void *pvParam)
  __STUB_ARGS__("(0x%p)", pvParam)

void CallbackImpl::Run(void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall)
  __STUB_ARGS__("(0x%p,%i,%llu)", pvParam, bIOFailure, hSteamAPICall)

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

void steam_bridge_SteamAPI_RegisterCallback(void *wrapper, int callback, int size)
{
  // TODO: Populate CallbackImpl with data?  (flags, iCallback?)
  WINE_TRACE("(0x%p,%i,%i)", wrapper, callback, size);
  CallbackImpl *c = new CallbackImpl(wrapper, size);
  __LOG_ARGS_MSG__("Logging wrapper for callback", "(0x%p)(0x%p,%i,%i)", c, wrapper, callback, size);
  SteamAPI_RegisterCallback(c, callback);
  // TODO: We should probabllly store the object.  Memory leaks and all
  //       that.  However, it's probably a safe guess that apps rarely (if ever).
}

} // extern "C"


