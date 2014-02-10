// steam_api_proxy.cpp - Defines the exported functions for the DLL application.

#include "stdafx.h"

#include "logging.h"
#include "steam_api_proxy.h"

extern "C"
{

STEAM_API_PROXY_API HSteamPipe SteamAPI_GetHSteamPipe()
  __STUB("")

STEAM_API_PROXY_API HSteamUser SteamAPI_GetHSteamUser()
  __STUB("")

STEAM_API_PROXY_API const char *SteamAPI_GetSteamInstallPath()
  __STUB("")

STEAM_API_PROXY_API bool SteamAPI_IsSteamRunning()
  __STUB("")

STEAM_API_PROXY_API void SteamAPI_RegisterCallResult(void *pCallback,
    SteamAPICall_t hAPICall)
  __STUB("(0x%p,%lu)", pCallback, hAPICall)

STEAM_API_PROXY_API void SteamAPI_SetBreakpadAppID(uint32 unAppID)
  __STUB("(%u)", unAppID)

STEAM_API_PROXY_API void SteamAPI_SetMiniDumpComment(const char *pchMsg)
  __STUB("(\"%s\")", pchMsg)

STEAM_API_PROXY_API void SteamAPI_SetTryCatchCallbacks(bool bTryCatchCallbacks)
  __STUB("(%i)", bTryCatchCallbacks)

STEAM_API_PROXY_API void SteamAPI_UnregisterCallResult(class CCallbackBase *pCallback,
    SteamAPICall_t hAPICall)
  __STUB("(0x%p,%lu)", pCallback, hAPICall)

STEAM_API_PROXY_API void SteamAPI_UseBreakpadCrashHandler(
    char const *pchVersion, char const *pchDate, char const *pchTime,
    bool bFullMemoryDumps, void *pvContext,
    PFNPreMinidumpCallback m_pfnPreMinidumpCallback)
  __STUB("(\"%s\",\"%s\",\"%s\",%i,0x%p,0x%p)", pchVersion, pchDate, pchTime,
      bFullMemoryDumps, pvContext, m_pfnPreMinidumpCallback)

STEAM_API_PROXY_API void SteamAPI_WriteMiniDump(
    uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID)
  __STUB("(%u,0x%p,%u)", uStructuredExceptionCode, pvExceptionInfo, uBuildID)

STEAM_API_PROXY_API void SteamContentServer()
  __CANT_IMPLEMENT("")
STEAM_API_PROXY_API void SteamContentServerUtils()
  __CANT_IMPLEMENT("")
STEAM_API_PROXY_API void SteamContentServer_Init()
  __CANT_IMPLEMENT("")
STEAM_API_PROXY_API void SteamContentServer_RunCallbacks()
  __CANT_IMPLEMENT("")
STEAM_API_PROXY_API void SteamContentServer_Shutdown()
  __CANT_IMPLEMENT("")
STEAM_API_PROXY_API void *SteamController()
  __CANT_IMPLEMENT("")

STEAM_API_PROXY_API void *SteamGameServer()
  __STUB("")

STEAM_API_PROXY_API void *SteamGameServerApps()
  __CANT_IMPLEMENT("")

STEAM_API_PROXY_API void *SteamGameServerHTTP()
  __STUB("")

STEAM_API_PROXY_API void *SteamGameServerNetworking()
  __STUB("")

STEAM_API_PROXY_API void *SteamGameServerStats()
  __STUB("")

STEAM_API_PROXY_API void *SteamGameServerUtils()
  __STUB("")

STEAM_API_PROXY_API bool SteamGameServer_BSecure()
  __STUB("")

STEAM_API_PROXY_API HSteamPipe SteamGameServer_GetHSteamPipe()
  __STUB("")

STEAM_API_PROXY_API HSteamUser SteamGameServer_GetHSteamUser()
  __STUB("")

// Can probably just return 0, though it'll be easy to return the results
// from the mothership library if we have the function definition correct.
// Set as CANT_IMPLEMENT for now.
STEAM_API_PROXY_API uint32 SteamGameServer_GetIPCCallCount()
  __CANT_IMPLEMENT("")

STEAM_API_PROXY_API uint64 SteamGameServer_GetSteamID()
  __STUB("")

STEAM_API_PROXY_API bool SteamGameServer_Init(uint32 unIP, uint16 usSteamPort,
    uint16 usGamePort, uint16 usQueryPort, int eServerMode,
    const char *pchVersionString)
// TODO: uint16 is an unsigned short int, right?
  __STUB("(%u,%hu,%hu,%hu,%i,\"%s\")", unIP, usSteamPort, usGamePort,
      usQueryPort, eServerMode, pchVersionString)

STEAM_API_PROXY_API bool SteamGameServer_InitSafe(uint32 unIP,
    uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, int eServerMode,
    const char *pchVersionString)
  __STUB("(%u,%hu,%hu,%hu,%i,\"%s\")", unIP, usSteamPort, usGamePort,
      usQueryPort, eServerMode, pchVersionString)

STEAM_API_PROXY_API void SteamGameServer_RunCallbacks()
  __STUB("")

STEAM_API_PROXY_API void SteamGameServer_Shutdown()
  __STUB("")

STEAM_API_PROXY_API void *SteamHTTP()
  __STUB("")

STEAM_API_PROXY_API void *SteamMatchmaking()
  __STUB("")

STEAM_API_PROXY_API void *SteamMatchmakingServers()
  __STUB("")

STEAM_API_PROXY_API void *SteamNetworking()
  __STUB("")

STEAM_API_PROXY_API void *SteamRemoteStorage()
  __STUB("")

STEAM_API_PROXY_API void *SteamScreenshots()
  __STUB("")

STEAM_API_PROXY_API void *SteamUGC()
  __CANT_IMPLEMENT("")

STEAM_API_PROXY_API void *SteamUnifiedMessages()
  __STUB("")

STEAM_API_PROXY_API void *SteamUtils()
  __STUB("")

STEAM_API_PROXY_API HSteamUser Steam_GetHSteamUserCurrent()
  __STUB("")

// Strong suspicion that we won't be able to implement this one correctly,
// but leave as STUB for now.
STEAM_API_PROXY_API void Steam_RegisterInterfaceFuncs(void *hModule)
  __STUB("(0x%p)", hModule)

STEAM_API_PROXY_API void Steam_RunCallbacks(HSteamPipe hSteamPipe, bool bGameServerCallbacks)
  __STUB("(%i,%i)", hSteamPipe, bGameServerCallbacks)

// This is a variable, not a function.  Usage, however, might be ...problematic.
STEAM_API_PROXY_API void *g_pSteamClientGameServer = NULL;

} // extern "C"

