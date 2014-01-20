// callback_api.cpp - Implements various APIs functionality related to
//                    Steam callbacks.

#include "stdafx.h"

#include <steam_api_bridge.h>

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"

extern "C"
{
void callback_run(void *callback, int flags, void *data);
void callback_run_args(void *callback, int flags, void *data, bool ioFailure, 
    SteamAPICall_t steamAPICall);
} // extern "C"


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
  friend void callback_run(void *, int, void *);
  friend void callback_run_args(void *, int, void *, bool, SteamAPICall_t);
};

extern "C"
{


void callback_run(void *callback, int flags, void *data)
{
  CCallbackBase *c = (CCallbackBase *)(callback);
  // TODO: There HAS to be a better way to track the flags
  c->m_nCallbackFlags = flags;
  c->Run(data);
}

void callback_run_args(void *callback, int flags, void *data, bool ioFailure,
    SteamAPICall_t steamAPICall)
{
  CCallbackBase *c = (CCallbackBase *)(callback);
  c->m_nCallbackFlags = flags;
  c->Run(data, ioFailure, steamAPICall);
}

STEAM_API_PROXY_API void SteamAPI_RunCallbacks()
{
  __LOG_MSG__("Running callbacks...");
  steam_bridge_SteamAPI_RunCallbacks();
}

STEAM_API_PROXY_API void SteamAPI_RegisterCallback(
    class CCallbackBase *pCallback, int iCallback)
{
  __LOG_ARGS_MSG__("Registering Callback", "(0x%p,%i,%i)", pCallback,
      iCallback, pCallback->GetCallbackSizeBytes());
  state.addCallback(pCallback);
  steam_bridge_SteamAPI_RegisterCallback(&callback_run, &callback_run_args, 
      pCallback, iCallback, pCallback->GetCallbackSizeBytes());
}

}

