// steam_api_proxy.h - Defines all the exposed API calls (+variable).

#include "types.h"

// TODO: Reorder these in a more logical order.  Header order has no
//       impact on DLL symbol ordinals, which is their current order.
#define ___STEAMBRIDGE_META_API___
extern "C"
{

//// 'Core' functions:

STEAM_API_PROXY_API HSteamPipe GetHSteamPipe();
STEAM_API_PROXY_API HSteamUser GetHSteamUser();
STEAM_API_PROXY_API HSteamUser SteamAPI_GetHSteamUser();
STEAM_API_PROXY_API HSteamPipe SteamAPI_GetHSteamPipe();

// Note: *HSteamPipe are considered private wrapper functions.


// NOTE: Probably an AppId_t
STEAM_API_PROXY_API bool SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID);
STEAM_API_PROXY_API bool SteamAPI_IsSteamRunning();

// SteamAPI_Init takes a parameter if _PS3 is defined.  As this isn't
// enabled by default, I think it's reasonably safe that this is only for
// PS3 builds.
STEAM_API_PROXY_API bool SteamAPI_Init();
STEAM_API_PROXY_API bool SteamAPI_InitSafe();
STEAM_API_PROXY_API void SteamAPI_Shutdown();


//// Callback functions:

// void ... ( class CCallbackBase *pCallback, SteamAPICall_t hAPICall )
STEAM_API_PROXY_API void SteamAPI_RegisterCallResult(void *pCallback,
    SteamAPICall_t hAPICall);

// void ... ( class CCallbackBase *pCallback, int iCallback )
STEAM_API_PROXY_API void SteamAPI_RegisterCallback(
    class CCallbackBase *pCallback, int iCallback);

STEAM_API_PROXY_API void SteamAPI_RunCallbacks();


// void ... ( class CCallbackBase *pCallback, SteamAPICall_t hAPICall )
STEAM_API_PROXY_API void SteamAPI_UnregisterCallResult(
    class CCallbackBase *pCallback, SteamAPICall_t hAPICall);

// void ... ( class CCallbackBase *pCallback )
STEAM_API_PROXY_API void SteamAPI_UnregisterCallback(
    class CCallbackBase *pCallback);


//// Memory dump related functions?
// Probably won't ever be correctly implemented

// NOTE: unAppID is almost certainly an AppId_t, but it's an uint32 in the
//       reference header.
STEAM_API_PROXY_API void SteamAPI_SetBreakpadAppID(uint32 unAppID);
STEAM_API_PROXY_API void SteamAPI_SetMiniDumpComment(const char *pchMsg);
// void ... ( char const *pchVersion, char const *pchDate, 
//            char const *pchTime, bool bFullMemoryDumps, void *pvContext, 
//            PFNPreMinidumpCallback m_pfnPreMinidumpCallback )
STEAM_API_PROXY_API void SteamAPI_UseBreakpadCrashHandler(
    char const *pchVersion, char const *pchDate, char const *pchTime,
    bool bFullMemoryDumps, void *pvContext,
    PFNPreMinidumpCallback m_pfnPreMinidumpCallback);

STEAM_API_PROXY_API void SteamAPI_WriteMiniDump(
    uint32 uStructuredExceptionCode, void *pvExceptionInfo, uint32 uBuildID);


/// Functionality (ISteam*) getter functions:

// ISteamApps *SteamApps()
STEAM_API_PROXY_API void *SteamApps();

// ISteamClient *SteamClient()
STEAM_API_PROXY_API void *SteamClient();

// This function does not appear in the Linux libsteam_api.so,
// though there are a few references to SteamController in the headers.
// It's persumably an interface to the upcoming Steam Controller hardware.
//
// Note that the live SteamOS boxes persumably have a release of
// libsteam_api.so containing this code, but until Valve updates their
// public Git repository, it can't be replicated.
// 
// For now, we'll assume it'll return a pointer to a ISteamController
// and takes no parameters (similar to other Steam*() functions), and we'll
// fail on execution.
STEAM_API_PROXY_API void *SteamController();

// ISteamFriends * ... ()
STEAM_API_PROXY_API void *SteamFriends();

// ISteamHTTP * ... ()
STEAM_API_PROXY_API void *SteamHTTP();
// ISteamMatchmaking * ... ()
STEAM_API_PROXY_API void *SteamMatchmaking();
// ISteamMatchmakingServers * ... ()
STEAM_API_PROXY_API void *SteamMatchmakingServers();
// ISteamNetworking * ... ()
STEAM_API_PROXY_API void *SteamNetworking();
// ISteamRemoteStorage * ... ()
STEAM_API_PROXY_API void *SteamRemoteStorage();
// ISteamScreenshots * ... ()
STEAM_API_PROXY_API void *SteamScreenshots();

// This function does not appear in the public headers, nor the public
// libsteam_api.so.  Judging by the name, it likely returns a pointer.
STEAM_API_PROXY_API void *SteamUGC();

// ISteamUnifiedMessages * ... ()
STEAM_API_PROXY_API void *SteamUnifiedMessages();
// ISteamUser * ... ()
STEAM_API_PROXY_API void *SteamUser();
// ISteamUserStats * ... ()
STEAM_API_PROXY_API void *SteamUserStats();
// ISteamUtils * ... ()
STEAM_API_PROXY_API void *SteamUtils();

//// SteamGameServer related functions

// ISteamGameServer * ... ()
STEAM_API_PROXY_API void *SteamGameServer();

// This function does not appear in the public headers.
STEAM_API_PROXY_API void *SteamGameServerApps();

// ISteamHTTP * ... ()
STEAM_API_PROXY_API void *SteamGameServerHTTP();
// ISteamNetworking * ... ()
STEAM_API_PROXY_API void *SteamGameServerNetworking();
// ISteamGameServerStats * ... ()
STEAM_API_PROXY_API void *SteamGameServerStats();
// ISteamUtils * ... ()
STEAM_API_PROXY_API void *SteamGameServerUtils();
STEAM_API_PROXY_API bool SteamGameServer_BSecure();
STEAM_API_PROXY_API HSteamPipe SteamGameServer_GetHSteamPipe();
STEAM_API_PROXY_API HSteamUser SteamGameServer_GetHSteamUser();

// This function appears in the compiled Linux DLL, but not the headers.
// Function appears as a member of a couple of non-networking classes
// (ISteamClient & ISteamUtils), where comments suggest it's a pure
// debugging function to determine how often Steam APIs are being called.
// We can probably safely return 0.
STEAM_API_PROXY_API uint32 SteamGameServer_GetIPCCallCount();
STEAM_API_PROXY_API uint64 SteamGameServer_GetSteamID();

// bool ... ( uint32 unIP, uint16 usSteamPort, uint16 usGamePort,
//            uint16 usQueryPort, EServerMode eServerMode,
//            const char *pchVersionString )
STEAM_API_PROXY_API bool SteamGameServer_Init(uint32 unIP, uint16 usSteamPort,
    uint16 usGamePort, uint16 usQueryPort, int eServerMode,
    const char *pchVersionString);

// bool ... ( uint32 unIP, uint16 usSteamPort, uint16 usGamePort,
//            uint16 usQueryPort, EServerMode eServerMode,
//            const char *pchVersionString )
STEAM_API_PROXY_API bool SteamGameServer_InitSafe(uint32 unIP,
    uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, int eServerMode,
    const char *pchVersionString);

STEAM_API_PROXY_API void SteamGameServer_RunCallbacks();
STEAM_API_PROXY_API void SteamGameServer_Shutdown();

//// SteamContentServer related functions

// All the steam content server stuff doesn't show up in the public
// headers.  This means we have the function name, but nothing else.  Due to
// the nature of __cdecl, nothing should blow up when this function is
// called, but it's unlikely we can safely return from it.
//
// Note there is a ISteamContentServer class that is forward declared, but
// otherwise not used.  SteamContentServer() likely returns a pointer to one.
//
// Theoretically, no users of steam_api.dll should use any of the
// SteamContentServer* functions, but they are nonetheless included to
// match the exported functions in the steam_api.dll.
//
STEAM_API_PROXY_API void SteamContentServer();
STEAM_API_PROXY_API void SteamContentServerUtils();
STEAM_API_PROXY_API void SteamContentServer_Init();
STEAM_API_PROXY_API void SteamContentServer_RunCallbacks();
STEAM_API_PROXY_API void SteamContentServer_Shutdown();

//// Steam 'internal' functions

// Note that the following are direct interfaces to SteamClient, and
// are considered at least semi 'internal' according to Steam documentation
STEAM_API_PROXY_API void Steam_RegisterInterfaceFuncs(void *hModule);
STEAM_API_PROXY_API void Steam_RunCallbacks(HSteamPipe hSteamPipe,
    bool bGameServerCallbacks);
STEAM_API_PROXY_API HSteamUser Steam_GetHSteamUserCurrent();
STEAM_API_PROXY_API const char *SteamAPI_GetSteamInstallPath();
// NOTE: Due to the nature of C++ exceptions, I doubt this works correctly
STEAM_API_PROXY_API void SteamAPI_SetTryCatchCallbacks(bool bTryCatchCallbacks);

// This is a variable, not a function.  Usage, however, might be ...problematic.
// ISteamClient *
STEAM_API_PROXY_API extern void *g_pSteamClientGameServer;

//// Meta API calls

#ifdef  ___STEAMBRIDGE_META_API___
// This won't cause problems, right?
STEAM_API_PROXY_API const char *Steam_proxy_version_string();
STEAM_API_PROXY_API const char *Steam_proxy_info_string();
#endif //___STEAMBRIDGE_META_API___

} // extern "C"
