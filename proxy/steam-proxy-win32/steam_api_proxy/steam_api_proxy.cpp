// steam_api_proxy.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <sstream>
#include <string>

#include "steam_api_proxy.h"

// TODO: This file is going to get well out of hand if it isn't split
//       until subfiles soon.

// Would be nice if this could take a message+vargs, so we can print
// the function arguments.  Also, turn this into a macro to handle the
// __FUNCSIG__ automagically.
__declspec(noreturn) static void __stub(const char *function)
{
  printf("Function %s is not implemented!\n", function);
  // TODO: Make this into a popup message box?
  exit(0);
}

#define __STUB__ { __stub(__FUNCSIG__); }

__declspec(noreturn) static void __cant_implement(const char *function)
{
  printf("Function %s cannot be implemented!\n", function);
  // TODO: Make this into a popup message box?
  exit(0);
}

#define __CANT_IMPLEMENT__ { __cant_implement(__FUNCSIG__); }

// TODO: Reorder these by a more logical order.  They are defined in
//       the header to match the steam_api.dll order (as close as possible).
//       That's not necessary here though.
extern "C"
{

STEAM_API_PROXY_API HSteamPipe GetHSteamPipe()
{
  return SteamAPI_GetHSteamPipe();
}

STEAM_API_PROXY_API HSteamUser GetHSteamUser()
{
  return SteamAPI_GetHSteamUser();
}

STEAM_API_PROXY_API HSteamPipe SteamAPI_GetHSteamPipe()
  __STUB__

STEAM_API_PROXY_API HSteamUser SteamAPI_GetHSteamUser()
  __STUB__

STEAM_API_PROXY_API const char *SteamAPI_GetSteamInstallPath()
  __STUB__

STEAM_API_PROXY_API bool SteamAPI_Init()
  __STUB__

STEAM_API_PROXY_API bool SteamAPI_InitSafe()
  __STUB__

STEAM_API_PROXY_API bool SteamAPI_IsSteamRunning()
  __STUB__

STEAM_API_PROXY_API void SteamAPI_RegisterCallResult(void *pCallback, SteamAPICall_t hAPICall)
  __STUB__

STEAM_API_PROXY_API void SteamAPI_RegisterCallback(void *pCallback, int iCallback)
  __STUB__

// Returns TRUE if the app should quit, as Steam will restart it through
// Steam.  This may or may not be considered 'DRM' in some sense.
STEAM_API_PROXY_API bool SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID)
  __STUB__

STEAM_API_PROXY_API void SteamAPI_RunCallbacks()
  __STUB__

STEAM_API_PROXY_API void SteamAPI_SetBreakpadAppID(uint32 unAppID)
  __STUB__

STEAM_API_PROXY_API void SteamAPI_SetMiniDumpComment(const char *pchMsg)
  __STUB__

STEAM_API_PROXY_API void SteamAPI_SetTryCatchCallbacks(bool bTryCatchCallbacks)
  __STUB__

STEAM_API_PROXY_API void SteamAPI_Shutdown()
  __STUB__

STEAM_API_PROXY_API void SteamAPI_UnregisterCallResult(void *pCallback, SteamAPICall_t hAPICall)
  __STUB__

STEAM_API_PROXY_API void SteamAPI_UnregisterCallback(void *pCallback)
  __STUB__

STEAM_API_PROXY_API void SteamAPI_UseBreakpadCrashHandler(char const *pchVersion, char const *pchDate, char const *pchTime, bool bFullMemoryDumps, void *pvContext, PFNPreMinidumpCallback m_pfnPreMinidumpCallback)
  __STUB__

STEAM_API_PROXY_API void SteamAPI_WriteMiniDump(uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID)
  __STUB__

STEAM_API_PROXY_API void *SteamApps()
  __STUB__

STEAM_API_PROXY_API void *SteamClient()
  __STUB__

STEAM_API_PROXY_API void SteamContentServer()
  __CANT_IMPLEMENT__
STEAM_API_PROXY_API void SteamContentServerUtils()
  __CANT_IMPLEMENT__
STEAM_API_PROXY_API void SteamContentServer_Init()
  __CANT_IMPLEMENT__
STEAM_API_PROXY_API void SteamContentServer_RunCallbacks()
  __CANT_IMPLEMENT__
STEAM_API_PROXY_API void SteamContentServer_Shutdown()
  __CANT_IMPLEMENT__
STEAM_API_PROXY_API void *SteamController()
  __CANT_IMPLEMENT__

STEAM_API_PROXY_API void *SteamFriends()
  __STUB__

STEAM_API_PROXY_API void *SteamGameServer()
  __STUB__

STEAM_API_PROXY_API void *SteamGameServerApps()
  __CANT_IMPLEMENT__

STEAM_API_PROXY_API void *SteamGameServerHTTP()
  __STUB__

STEAM_API_PROXY_API void *SteamGameServerNetworking()
  __STUB__

STEAM_API_PROXY_API void *SteamGameServerStats()
  __STUB__

STEAM_API_PROXY_API void *SteamGameServerUtils()
  __STUB__

STEAM_API_PROXY_API bool SteamGameServer_BSecure()
  __STUB__

STEAM_API_PROXY_API HSteamPipe SteamGameServer_GetHSteamPipe()
  __STUB__

STEAM_API_PROXY_API HSteamUser SteamGameServer_GetHSteamUser()
  __STUB__

// Can probably return 0, or even straight return the results from the
// mothership library.
STEAM_API_PROXY_API uint32 SteamGameServer_GetIPCCallCount()
  __CANT_IMPLEMENT__

// SteamIDs are a uint64 and not a typedef?  Bad Valve!
STEAM_API_PROXY_API uint64 SteamGameServer_GetSteamID()
  __STUB__

STEAM_API_PROXY_API bool SteamGameServer_Init(uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, int eServerMode, const char *pchVersionString )
  __STUB__

STEAM_API_PROXY_API bool SteamGameServer_InitSafe(uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, int eServerMode, const char *pchVersionString)
  __STUB__

STEAM_API_PROXY_API void SteamGameServer_RunCallbacks()
  __STUB__

STEAM_API_PROXY_API void SteamGameServer_Shutdown()
  __STUB__

STEAM_API_PROXY_API void *SteamHTTP()
  __STUB__

STEAM_API_PROXY_API void *SteamMatchmaking()
  __STUB__

STEAM_API_PROXY_API void *SteamMatchmakingServers()
  __STUB__

STEAM_API_PROXY_API void *SteamNetworking()
  __STUB__

STEAM_API_PROXY_API void *SteamRemoteStorage()
  __STUB__

STEAM_API_PROXY_API void *SteamScreenshots()
  __STUB__

STEAM_API_PROXY_API void *SteamUGC()
  __CANT_IMPLEMENT__

STEAM_API_PROXY_API void *SteamUnifiedMessages()
  __STUB__

STEAM_API_PROXY_API void *SteamUser()
  __STUB__

STEAM_API_PROXY_API void *SteamUserStats()
  __STUB__

STEAM_API_PROXY_API void *SteamUtils()
  __STUB__


} // extern "C"

