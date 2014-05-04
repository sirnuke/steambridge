// callback_api.cpp - Implements various APIs functionality related to
//                    Steam callbacks
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include "stdafx.h"

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"

#include <steam_api_bridge.h>

extern "C"
{
void callback_run(void *callback, int flags, void *data);
void callback_run_args(void *callback, int flags, void *data, bool ioFailure, 
    SteamAPICall_t steamAPICall);
} // extern "C"

// TODO: Add traces and whatnot to all this
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
  friend void SteamAPI_RegisterCallback(class CCallbackBase *, int);
  friend void SteamAPI_UnregisterCallback(class CCallbackBase *);
};

extern "C"
{

void callback_run(void *callback, int flags, void *data)
{
  __TRACE("(0x%p,%i,0x%p)", callback, flags, data);
  CCallbackBase *c = (CCallbackBase *)(callback);

  // TODO: Probably not setting the flags via this function.
  // c->m_nCallbackFlags = flags;

  __LOG("callback_run executing on func (0x%p) for callback wrapper (0x%p) data (0x%p) size (%i)",
      &callback_run, callback, data, c->GetCallbackSizeBytes());

  c->Run(data);

  __LOG("callback_run complete on func (0x%p) for callback wrapper (0x%p) data (0x%p) size (%i)",
      &callback_run, callback, data, c->GetCallbackSizeBytes());
}

void callback_run_args(void *callback, int flags, void *data, bool ioFailure,
    SteamAPICall_t steamAPICall)
{
  __TRACE("(0x%p,%i,0x%p,%i,%lu)", callback, flags, data, ioFailure, steamAPICall);
  CCallbackBase *c = (CCallbackBase *)(callback);

  // TODO: It's unlikely that the flags will just random change such
  //       that we'll need to manually set them here.  It seems like
  //       Registered is only set in the corresponding SteamAPI calls,
  //       and the game server flag is entirely client controlled.
  // c->m_nCallbackFlags = flags;

  __LOG("callback_run_args executing on func (0x%p) for wrapper (0x%p), data (0x%p) size (%i), iofailure (%i) APICall (%lu)",
    &callback_run_args, callback, data, c->GetCallbackSizeBytes(), ioFailure, steamAPICall);

  c->Run(data, ioFailure, steamAPICall);
}

STEAM_API_PROXY_API void SteamAPI_RunCallbacks()
{
  //__TRACE("()");
  SteamAPI_RunCallbacks_();
}

STEAM_API_PROXY_API void SteamAPI_RegisterCallback(class CCallbackBase *pCallback, int iCallback)
{
  __TRACE("(0x%p,%i)", pCallback, iCallback);
  __LOG("Registering Callback (0x%p) iCallback (%i) size (%i)", pCallback, iCallback,
     pCallback->GetCallbackSizeBytes());

  state.addCallback(pCallback);
  int flags = SteamAPI_RegisterCallback_(&callback_run, &callback_run_args, pCallback, iCallback,
      pCallback->GetCallbackSizeBytes());

  __LOG("Done registering callback (0x%p) old-flags=%i new-flags=%i; old-callbackid=%i new-callbackid=%i",
      pCallback, pCallback->m_nCallbackFlags, flags, pCallback->m_iCallback, iCallback);

  // Flags gets updated after RegisterCallback (and persumably other
  // similar functions).
  pCallback->m_nCallbackFlags = flags;
  // Note that bridge asserts that it's CCallbackBase's iCallback matches
  // the original parameter, so it's safe to forcibly set pCallback's
  // iCallback.
  pCallback->m_iCallback = iCallback;
  // TODO: Any more parameters that we might need to set?  Don't seem
  //       to be the case, as flags+iCallback are the only two exposed
  //       to the SteamAPI library itself.
}

STEAM_API_PROXY_API void SteamAPI_UnregisterCallback(class CCallbackBase *pCallback)
{
  __TRACE("(0x%p)", pCallback);
  __LOG("Unregistering callback (0x%p)", pCallback);
  // TODO: Update flags or something, anything?
  SteamAPI_UnregisterCallback_(pCallback);
}

}

