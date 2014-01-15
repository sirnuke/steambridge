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

//STEAM_API_PROXY_API int fnsteam_api_proxy(void);
/*
6 stub SteamAPI_Init
7 stub SteamAPI_InitSafe
8 stub SteamAPI_IsSteamRunning
9 stub SteamAPI_RegisterCallResult
10 stub SteamAPI_RegisterCallback
11 stub SteamAPI_RestartAppIfNecessary
12 stub SteamAPI_RunCallbacks
13 stub SteamAPI_SetBreakpadAppID
14 stub SteamAPI_SetMiniDumpComment
15 stub SteamAPI_SetTryCatchCallbacks
16 stub SteamAPI_Shutdown
17 stub SteamAPI_UnregisterCallResult
18 stub SteamAPI_UnregisterCallback
19 stub SteamAPI_UseBreakpadCrashHandler
20 stub SteamAPI_WriteMiniDump
21 stub SteamApps
22 stub SteamClient
23 stub SteamContentServer
24 stub SteamContentServerUtils
25 stub SteamContentServer_Init
26 stub SteamContentServer_RunCallbacks
27 stub SteamContentServer_Shutdown
28 stub SteamController
29 stub SteamFriends
30 stub SteamGameServer
31 stub SteamGameServerApps
32 stub SteamGameServerHTTP
33 stub SteamGameServerNetworking
34 stub SteamGameServerStats
35 stub SteamGameServerUtils
36 stub SteamGameServer_BSecure
37 stub SteamGameServer_GetHSteamPipe
38 stub SteamGameServer_GetHSteamUser
39 stub SteamGameServer_GetIPCCallCount
40 stub SteamGameServer_GetSteamID
41 stub SteamGameServer_Init
42 stub SteamGameServer_InitSafe
43 stub SteamGameServer_RunCallbacks
44 stub SteamGameServer_Shutdown
45 stub SteamHTTP
46 stub SteamMatchmaking
47 stub SteamMatchmakingServers
48 stub SteamNetworking
49 stub SteamRemoteStorage
50 stub SteamScreenshots
51 stub SteamUGC
52 stub SteamUnifiedMessages
53 stub SteamUser
54 stub SteamUserStats
55 stub SteamUtils
56 stub Steam_GetHSteamUserCurrent
57 stub Steam_RegisterInterfaceFuncs
58 stub Steam_RunCallbacks
59 stub g_pSteamClientGameServer
*/

} // extern "C"
