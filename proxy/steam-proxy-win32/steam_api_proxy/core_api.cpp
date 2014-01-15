// core_api.cpp - Implements various core (init, shutdown, etc) functions.

#include "stdafx.h"

#include "logging.h"
#include "steam_api_proxy.h"

extern "C"
{

// Returns TRUE if the app should quit, as Steam will restart it through
// Steam.  This may or may not be considered 'DRM' in some sense.
//
// Discovered case in Da Wild that calls this function before any sort
// of init calls.  Not sure whether this is the 'correct' behavior'.  Also,
// unOwnAppID doesn't correspond to the value in steam_appid.txt (?).
//
STEAM_API_PROXY_API bool SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID)
{
  __LOG_MSG__("(%u): overriding to FALSE", unOwnAppID);
  return false;
}

// SteamAPI_Init almost certainly won't work 100% correctly, as the
// Linux side libsteam_api.so is extremely unlikely to match the Windows
// steam_api.dll.  It appears it's just a convient default wrapper for
// InitSafe and SAFE friends, so we'll redirect to that for now.
//
// Note that in testing, forcing a failure return causes the test app
// (Waveform) to fail immediately.  Some apps may continue to run, though
// that defeats the purpose of using this project.
STEAM_API_PROXY_API bool SteamAPI_Init()
{
  // TODO: Need to lookup the application, and probably record somewhere
  //       that we aren't actually using the SAFE API.
  return SteamAPI_InitSafe();
}

STEAM_API_PROXY_API bool SteamAPI_InitSafe()
{
  __LOG_MSG__(": Overriding to failure (FALSE)");
  return false;
}




// According to steam_api.h:
// "backwards compat export, passes through to SteamAPI_ variant"
// Can do!
STEAM_API_PROXY_API HSteamPipe GetHSteamPipe()
{
  return SteamAPI_GetHSteamPipe();
}

STEAM_API_PROXY_API HSteamUser GetHSteamUser()
{
  return SteamAPI_GetHSteamUser();
}


} // extern "C"

