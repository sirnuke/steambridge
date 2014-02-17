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
STEAM_API_BRIDGE_API int SteamAPI_RegisterCallback_(steam_bridge_CallbackRunFunc, steam_bridge_CallbackRunArgsFunc, void *, int, int);
STEAM_API_BRIDGE_API void SteamAPI_UnregisterCallback_(void *);
STEAM_API_BRIDGE_API void SteamAPI_RunCallbacks_();

// SteamClient API Calls
STEAM_API_BRIDGE_API ISteamClient *SteamClient_();
STEAM_API_BRIDGE_API void SteamClient_SetWarningMessageHook(ISteamClient *, SteamAPIWarningMessageHook_t);

// SteamUser API calls
STEAM_API_BRIDGE_API ISteamUser *SteamUser_();
STEAM_API_BRIDGE_API HSteamUser SteamUser_GetHSteamUser(ISteamUser *);

// TODO: This returns a 'CSteamID', which is a set 64-bits.
//       It's relatively cleanly converted between uint64 and the struct,
//       BUT depending on the API definition, how they are returned
//       changes.  32-bit ints are returned as EAX (easy), 64-bit ints
//       are returned as EAX+EDX (harder), and struct use some black magic
//       that doesn't appear to be correctly supported by Winelib.
//       The work around is either to return as a 64-bit int, or store
//       the result in a pointer argument.

STEAM_API_BRIDGE_API void SteamUser_GetSteamID(ISteamUser *, CSteamID *);
STEAM_API_BRIDGE_API bool SteamUser_BLoggedOn(ISteamUser *);
STEAM_API_BRIDGE_API int SteamUser_InitiateGameConnection(ISteamUser *, void *, int, CSteamID, uint32, uint16, bool);
STEAM_API_BRIDGE_API void SteamUser_TerminateGameConnection(ISteamUser *, uint32, uint16);
STEAM_API_BRIDGE_API void SteamUser_TrackAppUsageEvent(ISteamUser *, CGameID, int, const char *);
STEAM_API_BRIDGE_API bool SteamUser_GetUserDataFolder(ISteamUser *, char *, int);
STEAM_API_BRIDGE_API void SteamUser_StartVoiceRecording(ISteamUser *);
STEAM_API_BRIDGE_API void SteamUser_StopVoiceRecording(ISteamUser *);
STEAM_API_BRIDGE_API EVoiceResult SteamUser_GetAvailableVoice(ISteamUser *, uint32 *, uint32 *, uint32);
STEAM_API_BRIDGE_API EVoiceResult SteamUser_GetVoice(ISteamUser *, bool, void *, uint32, uint32 *, bool , void *, uint32, uint32 *, uint32);
STEAM_API_BRIDGE_API EVoiceResult SteamUser_DecompressVoice(ISteamUser *, const void *, uint32, void *, uint32, uint32 *, uint32);
STEAM_API_BRIDGE_API uint32 SteamUser_GetVoiceOptimalSampleRate(ISteamUser *);
STEAM_API_BRIDGE_API HAuthTicket SteamUser_GetAuthSessionTicket(ISteamUser *, void *, int, uint32 *);
STEAM_API_BRIDGE_API EBeginAuthSessionResult SteamUser_BeginAuthSession(ISteamUser *, const void *, int, CSteamID);
STEAM_API_BRIDGE_API void SteamUser_EndAuthSession(ISteamUser *, CSteamID);
STEAM_API_BRIDGE_API void SteamUser_CancelAuthTicket(ISteamUser *, HAuthTicket);
STEAM_API_BRIDGE_API EUserHasLicenseForAppResult SteamUser_UserHasLicenseForApp(ISteamUser *, CSteamID, AppId_t);
STEAM_API_BRIDGE_API bool SteamUser_BIsBehindNAT(ISteamUser *);
STEAM_API_BRIDGE_API void SteamUser_AdvertiseGame(ISteamUser *, CSteamID, uint32, uint16);
STEAM_API_BRIDGE_API SteamAPICall_t SteamUser_RequestEncryptedAppTicket(ISteamUser *, void *, int);
STEAM_API_BRIDGE_API bool SteamUser_GetEncryptedAppTicket(ISteamUser *, void *, int, uint32 *);

// SteamFriends API calls
STEAM_API_BRIDGE_API ISteamFriends *SteamFriends_();
STEAM_API_BRIDGE_API const char *SteamFriends_GetPersonaName(ISteamFriends *);
STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_SetPersonaName(ISteamFriends *, const char *);
STEAM_API_BRIDGE_API EPersonaState SteamFriends_GetPersonaState(ISteamFriends *);
STEAM_API_BRIDGE_API int SteamFriends_GetFriendCount(ISteamFriends *, int);
STEAM_API_BRIDGE_API void SteamFriends_GetFriendByIndex(ISteamFriends *, int, int, CSteamID *);
STEAM_API_BRIDGE_API EFriendRelationship SteamFriends_GetFriendRelationship(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API EPersonaState SteamFriends_GetFriendPersonaState(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API const char *SteamFriends_GetFriendPersonaName(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API bool SteamFriends_GetFriendGamePlayed(ISteamFriends *, CSteamID, FriendGameInfo_t *);
STEAM_API_BRIDGE_API const char *SteamFriends_GetFriendPersonaNameHistory(ISteamFriends *, CSteamID, int);
STEAM_API_BRIDGE_API bool SteamFriends_HasFriend(ISteamFriends *, CSteamID, int);
STEAM_API_BRIDGE_API int SteamFriends_GetClanCount(ISteamFriends *);
STEAM_API_BRIDGE_API void SteamFriends_GetClanByIndex(ISteamFriends *, int, CSteamID *);
STEAM_API_BRIDGE_API const char *SteamFriends_GetClanName(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API const char *SteamFriends_GetClanTag(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API bool SteamFriends_GetClanActivityCounts(ISteamFriends *, CSteamID, int *, int *, int *);
STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_DownloadClanActivityCounts(ISteamFriends *, CSteamID *, int);
STEAM_API_BRIDGE_API int SteamFriends_GetFriendCountFromSource(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API void GetFriendFromSourceByIndex(ISteamFriends *, CSteamID, int, CSteamID *);
STEAM_API_BRIDGE_API bool SteamFriends_IsUserInSource(ISteamFriends *, CSteamID, CSteamID);
STEAM_API_BRIDGE_API void SteamFriends_SetInGameVoiceSpeaking(ISteamFriends *, CSteamID, bool);
STEAM_API_BRIDGE_API void SteamFriends_ActivateGameOverlay(ISteamFriends *, const char *);
STEAM_API_BRIDGE_API void SteamFriends_ActivateGameOverlayToUser(ISteamFriends *, const char *, CSteamID);
STEAM_API_BRIDGE_API void SteamFriends_ActivateGameOverlayToWebPage(ISteamFriends *, const char *);
STEAM_API_BRIDGE_API void SteamFriends_ActivateGameOverlayToStore(ISteamFriends *, AppId_t, EOverlayToStoreFlag);
STEAM_API_BRIDGE_API STEAM_API_BRIDGE_API void SteamFriends_SetPlayedWith(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API void SteamFriends_ActivateGameOverlayInviteDialog(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API int SteamFriends_GetSmallFriendAvatar(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API int SteamFriends_GetMediumFriendAvatar(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API int SteamFriends_GetLargeFriendAvatar(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API bool SteamFriends_RequestUserInformation(ISteamFriends *, CSteamID, bool);
STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_RequestClanOfficerList(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API void SteamFriends_GetClanOwner(ISteamFriends *steamFriends, CSteamID, CSteamID *);
STEAM_API_BRIDGE_API int SteamFriends_GetClanOfficerCount(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API void SteamFriends_GetClanOfficerByIndex(ISteamFriends *, CSteamID, int, CSteamID *);
STEAM_API_BRIDGE_API uint32 SteamFriends_GetUserRestrictions(ISteamFriends *);
STEAM_API_BRIDGE_API bool SteamFriends_SetRichPresence(ISteamFriends *, const char *, const char *);
STEAM_API_BRIDGE_API void SteamFriends_ClearRichPresence(ISteamFriends *);
STEAM_API_BRIDGE_API const char *SteamFriends_GetFriendRichPresence(ISteamFriends *, CSteamID, const char *);
STEAM_API_BRIDGE_API int SteamFriends_GetFriendRichPresenceKeyCount(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API const char *SteamFriends_GetFriendRichPresenceKeyByIndex(ISteamFriends *, CSteamID, int);
STEAM_API_BRIDGE_API void SteamFriends_RequestFriendRichPresence(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API bool SteamFriends_InviteUserToGame(ISteamFriends *, CSteamID, const char *);
STEAM_API_BRIDGE_API int SteamFriends_GetCoplayFriendCount(ISteamFriends *);
STEAM_API_BRIDGE_API void SteamFriends_GetCoplayFriend(ISteamFriends *, int, CSteamID *);
STEAM_API_BRIDGE_API int SteamFriends_GetFriendCoplayTime(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API AppId_t SteamFriends_GetFriendCoplayGame(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_JoinClanChatRoom(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API bool SteamFriends_LeaveClanChatRoom(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API int SteamFriends_GetClanChatMemberCount(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API void SteamFriends_GetChatMemberByIndex(ISteamFriends *, CSteamID, int, CSteamID *);
STEAM_API_BRIDGE_API bool SteamFriends_SendClanChatMessage(ISteamFriends *, CSteamID, const char *);
STEAM_API_BRIDGE_API int SteamFriends_GetClanChatMessage(ISteamFriends *, CSteamID, int, void *, int, EChatEntryType *, CSteamID *);
STEAM_API_BRIDGE_API bool SteamFriends_IsClanChatAdmin(ISteamFriends *, CSteamID, CSteamID);
STEAM_API_BRIDGE_API bool SteamFriends_IsClanChatWindowOpenInSteam(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API bool SteamFriends_OpenClanChatWindowInSteam(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API bool SteamFriends_CloseClanChatWindowInSteam(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API bool SteamFriends_SetListenForFriendsMessages(ISteamFriends *, bool);
STEAM_API_BRIDGE_API bool SteamFriends_ReplyToFriendMessage(ISteamFriends *, CSteamID, const char *);
STEAM_API_BRIDGE_API int SteamFriends_GetFriendMessage(ISteamFriends *, CSteamID, int, void *, int, EChatEntryType *);
STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_GetFollowerCount(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_IsFollowing(ISteamFriends *, CSteamID);
STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_EnumerateFollowingList(ISteamFriends *, uint32);

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
