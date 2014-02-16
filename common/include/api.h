// api.h - Defines the public API (at least the relevant part)
//
// !!!!!!!!!
// CRITICAL: This file is shared with the win32 Visual Studio project
//           and the Linux Winelib.  Any changes here must be compatable with both
//           Linux and Windows, and changes must update both projects.
// !!!!!!!!!


#ifndef  ___STEAM_API_BRIDGE_API_H___
#define  ___STEAM_API_BRIDGE_API_H___

// TODO: There might be a better way to handle this
#ifndef  STEAM_API_BRIDGE_API 
#define  STEAM_API_BRIDGE_API 
#endif //STEAM_API_BRIDGE_API 

// Callback function pointer types
// See documentation in callback.cpp for more information about this
typedef void (*steam_bridge_CallbackRunFunc)(void *wrapper, int flags,
    void *data);
typedef void (*steam_bridge_CallbackRunArgsFunc)(void *wrapper, int flags,
    void *data, bool ioFailure, SteamAPICall_t steamAPICall);
typedef void (*steam_bridge_WarningHookFunc)(int severity,
    const char *message);

class ISteamClient;
class ISteamUser;
class ISteamFriends;
class ISteamApps;
class ISteamUserStats;
class ISteamUtils;

extern "C" {

// Core API Calls
STEAM_API_BRIDGE_API bool steam_bridge_SteamAPI_InitSafe();
STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_Shutdown();
// TODO: Handle callback flags better, probably don't need/want to
//       return an int here.
STEAM_API_BRIDGE_API int steam_bridge_SteamAPI_RegisterCallback(
    steam_bridge_CallbackRunFunc run, steam_bridge_CallbackRunArgsFunc runargs,
    void *object, int callback, int size);
STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_UnregisterCallback(
    void *object);
STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_RunCallbacks();

// SteamClient API Calls
STEAM_API_BRIDGE_API ISteamClient *steam_bridge_SteamClient();
STEAM_API_BRIDGE_API void steam_bridge_SteamClient_SetWarningMessageHook(
    ISteamClient *steamClient, SteamAPIWarningMessageHook_t func);

// SteamUser API calls
STEAM_API_BRIDGE_API ISteamUser *steam_bridge_SteamUser();

// TODO: This returns a 'CSteamID', which is a set 64-bits.
//       It's relatively cleanly converted between uint64 and the struct,
//       BUT depending on the API definition, how they are returned
//       changes.  32-bit ints are returned as EAX (easy), 64-bit ints
//       are returned as EAX+EDX (harder), and struct use some black magic
//       that doesn't appear to be correctly supported by Winelib.
//       The work around is either to return as a 64-bit int, or store
//       the result in a pointer argument.

STEAM_API_BRIDGE_API void steam_bridge_SteamUser_GetSteamID(
    ISteamUser *steamUser, CSteamID *id);
STEAM_API_BRIDGE_API bool steam_bridge_SteamUser_BLoggedOn(
    ISteamUser *steamUser);
STEAM_API_BRIDGE_API int steam_bridge_SteamUser_InitiateGameConnection(
    ISteamUser *steamUser, void *pAuthBlob, int cbMaxAuthBlob,
    CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer,
    bool bSecure);
STEAM_API_BRIDGE_API void steam_bridge_SteamUser_TerminateGameConnection(
    ISteamUser *steamUser, uint32 unIPServer, uint16 usPortServer);

// SteamFriends API calls
STEAM_API_BRIDGE_API ISteamFriends *steam_bridge_SteamFriends();
STEAM_API_BRIDGE_API const char *steam_bridge_SteamFriends_GetPersonaName(
    ISteamFriends *steamFriends);
STEAM_API_BRIDGE_API int steam_bridge_SteamFriends_GetFriendCount(
    ISteamFriends *steamFriends, int iFriendFlags);
STEAM_API_BRIDGE_API void steam_bridge_SteamFriends_SetPlayedWith(
    ISteamFriends *steamFriends, CSteamID steamIDUserPlayedWith);

// SteamApps API Calls
STEAM_API_BRIDGE_API ISteamApps *steam_bridge_SteamApps();
STEAM_API_BRIDGE_API bool steam_bridge_SteamApps_BIsSubscribedApp(
    ISteamApps *steamApps, AppId_t appId);
STEAM_API_BRIDGE_API const char *steam_bridge_SteamApps_GetCurrentGameLanguage(
    ISteamApps *steamApps);

// SteamUserStats API Calls
STEAM_API_BRIDGE_API ISteamUserStats *steam_bridge_SteamUserStats();
STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_RequestCurrentStats(
    ISteamUserStats *steamUserStats);
STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_GetStatI(
    ISteamUserStats *steamUserStats, const char *pchName, int32 *pData);
STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_GetStatF(
    ISteamUserStats *steamUserStats, const char *pchName, float *pData);
STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_SetStatI(
    ISteamUserStats *steamUserStats, const char *pchName, int32 nData);
STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_SetStatF(
    ISteamUserStats *steamUserStats, const char *pchName, float fData);
STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_UpdateAvgRateStat(
    ISteamUserStats *steamUserStats, const char *pchName,
    float flCountThisSession, double dSessionLength);
STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_GetAchievement(
    ISteamUserStats *steamUserStats, const char *pchName, bool *pbAchieved);
STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_SetAchievement(
    ISteamUserStats *steamUserStats, const char *pchName);
STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_ClearAchievement(
    ISteamUserStats *steamUserStats, const char *pchName);
STEAM_API_BRIDGE_API bool
  steam_bridge_SteamUserStats_GetAchievementAndUnlockTime(
    ISteamUserStats *steamUserStats, const char *pchName, bool *pbAchieved,
    uint32 *punUnlockTime);
STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_StoreStats(
    ISteamUserStats *steamUserStats);
STEAM_API_BRIDGE_API int steam_bridge_SteamUserStats_GetAchievementIcon(
    ISteamUserStats *steamUserStats, const char *pchName);
STEAM_API_BRIDGE_API const char *
  steam_bridge_SteamUserStats_GetAchievementDisplayAttribute(
    ISteamUserStats *steamUserStats, const char *pchName, const char *pchKey);
STEAM_API_BRIDGE_API uint32 steam_bridge_SteamUserStats_GetNumAchievements(
    ISteamUserStats *steamUserStats);
STEAM_API_BRIDGE_API const char *steam_bridge_SteamUserStats_GetAchievementName(
    ISteamUserStats *steamUserStats, uint32 iAchievement);

// SteamUtils API Calls
STEAM_API_BRIDGE_API ISteamUtils *steam_bridge_SteamUtils();
STEAM_API_BRIDGE_API void steam_bridge_SteamUtils_SetOverlayNotificationPosition(
    ISteamUtils *steamUtils, int eNotificationPosition);

// Meta API Calls
STEAM_API_BRIDGE_API const char *steam_bridge_version_string();
STEAM_API_BRIDGE_API const char *steam_bridge_info_string();

} // extern "C"

#endif //___STEAM_API_BRIDGE_API_H___
