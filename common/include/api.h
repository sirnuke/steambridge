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

class ISteamClient;
class ISteamUser;
class ISteamFriends;
class ISteamApps;
class ISteamUserStats;
class ISteamUtils;

extern "C" {

// Core API Calls
STEAM_API_BRIDGE_API bool SteamAPI_InitSafe_();
STEAM_API_BRIDGE_API void SteamAPI_Shutdown_();
// TODO: Handle callback flags better, probably don't need/want to
//       return an int here.
STEAM_API_BRIDGE_API int SteamAPI_RegisterCallback_(steam_bridge_CallbackRunFunc run,
    steam_bridge_CallbackRunArgsFunc runargs, void *object, int callback, int size);
STEAM_API_BRIDGE_API void SteamAPI_UnregisterCallback_(void *object);
STEAM_API_BRIDGE_API void SteamAPI_RunCallbacks_();

// SteamClient API Calls
STEAM_API_BRIDGE_API ISteamClient *SteamClient_();
STEAM_API_BRIDGE_API void SteamClient_SetWarningMessageHook(ISteamClient *steamClient,
    SteamAPIWarningMessageHook_t func);

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
STEAM_API_BRIDGE_API ISteamUserStats *SteamUserStats_();
STEAM_API_BRIDGE_API bool SteamUserStats_RequestCurrentStats(ISteamUserStats *);
STEAM_API_BRIDGE_API bool SteamUserStats_GetStatI(ISteamUserStats *, const char *, int32 *);
STEAM_API_BRIDGE_API bool SteamUserStats_GetStatF(ISteamUserStats *, const char *, float *);
STEAM_API_BRIDGE_API bool SteamUserStats_SetStatI(ISteamUserStats *, const char *, int32);
STEAM_API_BRIDGE_API bool SteamUserStats_SetStatF(ISteamUserStats *, const char *, float);
STEAM_API_BRIDGE_API bool SteamUserStats_UpdateAvgRateStat(ISteamUserStats *, const char *, float, double);
STEAM_API_BRIDGE_API bool SteamUserStats_GetAchievement(ISteamUserStats *, const char *, bool *);
STEAM_API_BRIDGE_API bool SteamUserStats_SetAchievement(ISteamUserStats *, const char *);
STEAM_API_BRIDGE_API bool SteamUserStats_ClearAchievement(ISteamUserStats *, const char *);
STEAM_API_BRIDGE_API bool SteamUserStats_GetAchievementAndUnlockTime(ISteamUserStats *, const char *, bool *, uint32 *);
STEAM_API_BRIDGE_API bool SteamUserStats_StoreStats(ISteamUserStats *);
STEAM_API_BRIDGE_API int SteamUserStats_GetAchievementIcon(ISteamUserStats *, const char *);
STEAM_API_BRIDGE_API const char *SteamUserStats_GetAchievementDisplayAttribute(ISteamUserStats *, const char *, const char *);
STEAM_API_BRIDGE_API bool SteamUserStats_IndicateAchievementProgress(ISteamUserStats *, const char *, uint32, uint32);
STEAM_API_BRIDGE_API uint32 SteamUserStats_GetNumAchievements(ISteamUserStats *);
STEAM_API_BRIDGE_API const char *SteamUserStats_GetAchievementName(ISteamUserStats *, uint32);
STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_RequestUserStats(ISteamUserStats *, CSteamID);
STEAM_API_BRIDGE_API bool SteamUserStats_GetUserStatI(ISteamUserStats *, CSteamID, const char *, int32 *);
STEAM_API_BRIDGE_API bool SteamUserStats_GetUserStatF(ISteamUserStats *, CSteamID, const char *, float *);
STEAM_API_BRIDGE_API bool SteamUserStats_GetUserAchievement(ISteamUserStats *, CSteamID, const char *, bool *);
STEAM_API_BRIDGE_API bool SteamUserStats_GetUserAchievementAndUnlockTime(ISteamUserStats *, CSteamID, const char *, bool *, uint32 *);
STEAM_API_BRIDGE_API bool SteamUserStats_ResetAllStats(ISteamUserStats *, bool);
STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_FindOrCreateLeaderboard(ISteamUserStats *, const char *, ELeaderboardSortMethod, ELeaderboardDisplayType);
STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_FindLeaderboard(ISteamUserStats *, const char *);
STEAM_API_BRIDGE_API const char *SteamUserStats_GetLeaderboardName(ISteamUserStats *, SteamLeaderboard_t);
STEAM_API_BRIDGE_API int SteamUserStats_GetLeaderboardEntryCount(ISteamUserStats *, SteamLeaderboard_t);
STEAM_API_BRIDGE_API ELeaderboardSortMethod SteamUserStats_GetLeaderboardSortMethod(ISteamUserStats *, SteamLeaderboard_t);
STEAM_API_BRIDGE_API ELeaderboardDisplayType SteamUserStats_GetLeaderboardDisplayType(ISteamUserStats *, SteamLeaderboard_t);
STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_DownloadLeaderboardEntries(ISteamUserStats *, SteamLeaderboard_t, ELeaderboardDataRequest, int, int);
STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_DownloadLeaderboardEntriesForUsers(ISteamUserStats *, SteamLeaderboard_t, CSteamID *, int);
STEAM_API_BRIDGE_API bool SteamUserStats_GetDownloadedLeaderboardEntry(ISteamUserStats *, SteamLeaderboardEntries_t, int, LeaderboardEntry_t *, int32 *, int);
STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_UploadLeaderboardScore(ISteamUserStats *, SteamLeaderboard_t, ELeaderboardUploadScoreMethod, int32, const int32 *, int);
STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_AttachLeaderboardUGC(ISteamUserStats *, SteamLeaderboard_t, UGCHandle_t);
STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_GetNumberOfCurrentPlayers(ISteamUserStats *);
STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_RequestGlobalAchievementPercentages(ISteamUserStats *);
STEAM_API_BRIDGE_API int SteamUserStats_GetMostAchievedAchievementInfo(ISteamUserStats *, char *, uint32, float *, bool *);
STEAM_API_BRIDGE_API int SteamUserStats_GetNextMostAchievedAchievementInfo(ISteamUserStats *, int, char *, uint32, float *, bool *);
STEAM_API_BRIDGE_API bool SteamUserStats_GetAchievementAchievedPercent(ISteamUserStats *, const char *, float *);
STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_RequestGlobalStats(ISteamUserStats *, int);
STEAM_API_BRIDGE_API bool SteamUserStats_GetGlobalStatI(ISteamUserStats *, const char *, int64 *);
STEAM_API_BRIDGE_API bool SteamUserStats_GetGlobalStatD(ISteamUserStats *, const char *, double *);
STEAM_API_BRIDGE_API int32 SteamUserStats_GetGlobalStatHistoryI(ISteamUserStats *, const char *, int64 *, uint32);
STEAM_API_BRIDGE_API int32 SteamUserStats_GetGlobalStatHistoryD(ISteamUserStats *, const char *, double *, uint32);

// SteamUtils API Calls
STEAM_API_BRIDGE_API ISteamUtils *steam_bridge_SteamUtils();
STEAM_API_BRIDGE_API void steam_bridge_SteamUtils_SetOverlayNotificationPosition(
    ISteamUtils *steamUtils, int eNotificationPosition);

// Meta API Calls
STEAM_API_BRIDGE_API const char *steam_bridge_version_string();
STEAM_API_BRIDGE_API const char *steam_bridge_info_string();

} // extern "C"

#endif //___STEAM_API_BRIDGE_API_H___
