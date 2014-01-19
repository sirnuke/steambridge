// callback_api.cpp - Implements various APIs functionality related to
//                    Steam callbacks.

#include "stdafx.h"

#include <steam_api_bridge.h>

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"


class CCallbackBase
{
public:
	CCallbackBase() { m_nCallbackFlags = 0; m_iCallback = 0; }
	// don't add a virtual destructor because we export this binary interface across dll's
	virtual void Run( void *pvParam ) = 0;
	virtual void Run( void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall ) = 0;
	int GetICallback() { return m_iCallback; }
	virtual int GetCallbackSizeBytes() = 0;

protected:
	enum { k_ECallbackFlagsRegistered = 0x01, k_ECallbackFlagsGameServer = 0x02 };
  // No getter/settings on CallbackFlags, despite the values being set
  // by the steam_api library?  Bad Valve!
	uint8 m_nCallbackFlags;
	int m_iCallback;
	friend class CCallbackMgr;
  friend class CallbackWrapper;
};

class CallbackWrapper
{
  public:
    CallbackWrapper(CCallbackBase *parent) : parent(parent)
    {
      flags = parent->m_nCallbackFlags;
      callback = parent->m_iCallback;
    }

  private:
    CCallbackBase *parent;
    uint8 flags;
    int callback;
};

static void SteamAPI_RegisterCallbackReal(CCallbackBase *pCallback, int iCallback)
{
  // Create new CallbackWrapper if one doesn't already exist 
  // Set wrapper->callback to iCallback?
  // Pass stuff onto the bridge
  CallbackWrapper *wrapper = new CallbackWrapper(pCallback);
  state.addCallbackWrapper(wrapper);
  steam_bridge_SteamAPI_RegisterCallback(wrapper, iCallback, pCallback->GetCallbackSizeBytes());
}

extern "C"
{

STEAM_API_PROXY_API void SteamAPI_RunCallbacks()
{
  __LOG_MSG__("Running callbacks...");
  steam_bridge_SteamAPI_RunCallbacks();
}

STEAM_API_PROXY_API void SteamAPI_RegisterCallback(class CCallbackBase *pCallback, int iCallback)
{
  __LOG_ARGS_MSG__("Registering Callback", "(0x%p,%i)", pCallback, iCallback);
  SteamAPI_RegisterCallbackReal(pCallback, iCallback);
}

}

