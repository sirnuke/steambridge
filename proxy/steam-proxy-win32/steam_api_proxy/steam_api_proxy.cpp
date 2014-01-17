// steam_api_proxy.cpp - Defines the exported functions for the DLL application.

#include "stdafx.h"

#include "logging.h"
#include "steam_api_proxy.h"

// TODO: Send this off to a separate CPP file!
// TODO: Also, wrap it in a define of some sort, justincase we want to
//       build a version w/o it.
const char *steamredirect_version = "0";
const char *steamredirect_info = "[Add built information, web address, etc here]";

extern "C"
{

STEAM_API_PROXY_API HSteamPipe SteamAPI_GetHSteamPipe()
  __STUB__

STEAM_API_PROXY_API HSteamUser SteamAPI_GetHSteamUser()
  __STUB__

STEAM_API_PROXY_API const char *SteamAPI_GetSteamInstallPath()
  __STUB__

STEAM_API_PROXY_API bool SteamAPI_IsSteamRunning()
  __STUB__

STEAM_API_PROXY_API void SteamAPI_RegisterCallResult(void *pCallback, SteamAPICall_t hAPICall)
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
{
  __LOG_MSG__("Force overriding SteamFriends to return (NULL)...");
  return NULL;
}

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

// Can probably just return 0, though it'll be easy to return the results
// from the mothership library if we have the function definition correct.
// Set as CANT_IMPLEMENT for now.
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

STEAM_API_PROXY_API void *SteamUserStats()
  __STUB__

STEAM_API_PROXY_API void *SteamUtils()
  __STUB__

STEAM_API_PROXY_API HSteamUser Steam_GetHSteamUserCurrent()
  __STUB__

// Strong suspicion that we won't be able to implement this one correctly,
// but leave as STUB for now.
STEAM_API_PROXY_API void Steam_RegisterInterfaceFuncs(void *hModule)
  __STUB__

STEAM_API_PROXY_API void Steam_RunCallbacks(HSteamPipe hSteamPipe, bool bGameServerCallbacks)
  __STUB__

// This is a variable, not a function.  Usage, however, might be ...problematic.
STEAM_API_PROXY_API void *g_pSteamClientGameServer;

// TODO: Off with your heads!  To a new file!
STEAM_API_PROXY_API const char *SteamRedirect_version_string()
{
  return steamredirect_version;
}

STEAM_API_PROXY_API const char *SteamRedirect_info_string()
{
  return steamredirect_info;
}

} // extern "C"

