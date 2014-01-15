// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STEAM_API_PROXY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STEAM_API_PROXY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef STEAM_API_PROXY_EXPORTS
#define STEAM_API_PROXY_API __declspec(dllexport)
#else
#define STEAM_API_PROXY_API __declspec(dllimport)
#endif

#include "types.h"

extern "C"
{

STEAM_API_PROXY_API HSteamPipe GetHSteamPipe();
STEAM_API_PROXY_API HSteamUser GetHSteamUser();
STEAM_API_PROXY_API HSteamPipe SteamAPI_GetHSteamPipe();
STEAM_API_PROXY_API HSteamUser SteamAPI_GetHSteamUser();

STEAM_API_PROXY_API const char *SteamAPI_GetSteamInstallPath();

// SteamAPI_Init takes a parameter if _PS3 is defined.  As this isn't
// enabled by default, I think it's reasonably safe that this is only for
// PS3 builds.
STEAM_API_PROXY_API bool SteamAPI_Init();
STEAM_API_PROXY_API bool SteamAPI_InitSafe();

STEAM_API_PROXY_API bool SteamAPI_IsSteamRunning();

// void ... ( class CCallbackBase *pCallback, SteamAPICall_t hAPICall )
STEAM_API_PROXY_API void SteamAPI_RegisterCallResult(void *pCallback, SteamAPICall_t hAPICall);

// void ... ( class CCallbackBase *pCallback, int iCallback )
STEAM_API_PROXY_API void SteamAPI_RegisterCallback(void *pCallback, int iCallback);

STEAM_API_PROXY_API bool SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID);

STEAM_API_PROXY_API void SteamAPI_RunCallbacks();

STEAM_API_PROXY_API void SteamAPI_SetBreakpadAppID(uint32 unAppID);
STEAM_API_PROXY_API void SteamAPI_SetMiniDumpComment(const char *pchMsg);

STEAM_API_PROXY_API void SteamAPI_SetTryCatchCallbacks(bool bTryCatchCallbacks);

STEAM_API_PROXY_API void SteamAPI_Shutdown();

// void ... ( class CCallbackBase *pCallback, SteamAPICall_t hAPICall )
STEAM_API_PROXY_API void SteamAPI_UnregisterCallResult(void *pCallback, SteamAPICall_t hAPICall);

// void ... ( class CCallbackBase *pCallback )
STEAM_API_PROXY_API void SteamAPI_UnregisterCallback(void *pCallback);

// void ... ( char const *pchVersion, char const *pchDate, char const *pchTime, bool bFullMemoryDumps, void *pvContext, PFNPreMinidumpCallback m_pfnPreMinidumpCallback )
STEAM_API_PROXY_API void SteamAPI_UseBreakpadCrashHandler(char const *pchVersion, char const *pchDate, char const *pchTime, bool bFullMemoryDumps, void *pvContext, PFNPreMinidumpCallback m_pfnPreMinidumpCallback);

// void ... ( uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID )
STEAM_API_PROXY_API void SteamAPI_WriteMiniDump(uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID);

// ISteamApps *SteamApps()
STEAM_API_PROXY_API void *SteamApps();

// ISteamClient *SteamClient()
STEAM_API_PROXY_API void *SteamClient();

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
// match the ordinal/exported functions in the steam_api.dll.
//

STEAM_API_PROXY_API void SteamContentServer();
STEAM_API_PROXY_API void SteamContentServerUtils();
STEAM_API_PROXY_API void SteamContentServer_Init();
STEAM_API_PROXY_API void SteamContentServer_RunCallbacks();
STEAM_API_PROXY_API void SteamContentServer_Shutdown();

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

// bool ... ( uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString )
// TODO: enums without a type are just ints, right?  signed or
//       unsigned? 50% sure it's just an int
STEAM_API_PROXY_API bool SteamGameServer_Init(uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, int eServerMode, const char *pchVersionString );

// bool ... ( uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, EServerMode eServerMode, const char *pchVersionString )
STEAM_API_PROXY_API bool SteamGameServer_InitSafe(uint32 unIP, uint16 usSteamPort, uint16 usGamePort, uint16 usQueryPort, int eServerMode, const char *pchVersionString);

STEAM_API_PROXY_API void SteamGameServer_RunCallbacks();
STEAM_API_PROXY_API void SteamGameServer_Shutdown();

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

// This function does not appear in the public headers, nor the public libsteam_api.so.  Judging by the name and location in the DLL, it likely returns a pointer.
STEAM_API_PROXY_API void *SteamUGC();

// ISteamUnifiedMessages * ... ()
STEAM_API_PROXY_API void *SteamUnifiedMessages();
// ISteamUser * ... ()
STEAM_API_PROXY_API void *SteamUser();
// ISteamUserStats * ... ()
STEAM_API_PROXY_API void *SteamUserStats();
// ISteamUtils * ... ()
STEAM_API_PROXY_API void *SteamUtils();

STEAM_API_PROXY_API HSteamUser Steam_GetHSteamUserCurrent();
STEAM_API_PROXY_API void Steam_RegisterInterfaceFuncs(void *hModule);
STEAM_API_PROXY_API void Steam_RunCallbacks(HSteamPipe hSteamPipe, bool bGameServerCallbacks);

// This is a variable, not a function.  Usage, however, might be ...problematic.
// ISteamClient *
STEAM_API_PROXY_API extern void *g_pSteamClientGameServer;

// This won't cause problems, right?
STEAM_API_PROXY_API const char *SteamRedirect_version_string();
STEAM_API_PROXY_API const char *SteamRedirect_info_string();

} // extern "C"
