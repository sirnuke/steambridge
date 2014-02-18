// steam_api_bridge.cpp - Stub's the public bridge API
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include "stdafx.h"

#include <cstdlib>

#include <types.h>

#include "steam_api_bridge.h"

#define __STUB__ { __stub__(); }
 __declspec(noreturn) void __stub__()
 {
   exit(1);
 }

extern "C"
{
  STEAM_API_BRIDGE_API bool SteamAPI_InitSafe_() __STUB__;
  STEAM_API_BRIDGE_API void SteamAPI_Shutdown_() __STUB__;
  STEAM_API_BRIDGE_API int SteamAPI_RegisterCallback_(steam_bridge_CallbackRunFunc, steam_bridge_CallbackRunArgsFunc, void *, int, int) __STUB__;
  STEAM_API_BRIDGE_API void SteamAPI_UnregisterCallback_(void *) __STUB__;
  STEAM_API_BRIDGE_API void SteamAPI_RunCallbacks_() __STUB__;

  STEAM_API_BRIDGE_API ISteamClient *SteamClient_() __STUB__;
  STEAM_API_BRIDGE_API void SteamClient_SetWarningMessageHook(ISteamClient *, SteamAPIWarningMessageHook_t) __STUB__;

  STEAM_API_BRIDGE_API ISteamUser *SteamUser_() __STUB__;
  STEAM_API_BRIDGE_API HSteamUser SteamUser_GetHSteamUser(ISteamUser *) __STUB__;
  STEAM_API_BRIDGE_API void SteamUser_GetSteamID(ISteamUser *, CSteamID *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUser_BLoggedOn(ISteamUser *) __STUB__;
  STEAM_API_BRIDGE_API int SteamUser_InitiateGameConnection(ISteamUser *, void *, int, CSteamID, uint32, uint16, bool) __STUB__;
  STEAM_API_BRIDGE_API void SteamUser_TerminateGameConnection(ISteamUser *, uint32, uint16) __STUB__;
  STEAM_API_BRIDGE_API void SteamUser_TrackAppUsageEvent(ISteamUser *, CGameID, int, const char *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUser_GetUserDataFolder(ISteamUser *, char *, int) __STUB__;
  STEAM_API_BRIDGE_API void SteamUser_StartVoiceRecording(ISteamUser *) __STUB__;
  STEAM_API_BRIDGE_API void SteamUser_StopVoiceRecording(ISteamUser *) __STUB__;
  STEAM_API_BRIDGE_API EVoiceResult SteamUser_GetAvailableVoice(ISteamUser *, uint32 *, uint32 *, uint32) __STUB__;
  STEAM_API_BRIDGE_API EVoiceResult SteamUser_GetVoice(ISteamUser *, bool, void *, uint32, uint32 *, bool , void *, uint32, uint32 *, uint32) __STUB__;
  STEAM_API_BRIDGE_API EVoiceResult SteamUser_DecompressVoice(ISteamUser *, const void *, uint32, void *, uint32, uint32 *, uint32) __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamUser_GetVoiceOptimalSampleRate(ISteamUser *) __STUB__;
  STEAM_API_BRIDGE_API HAuthTicket SteamUser_GetAuthSessionTicket(ISteamUser *, void *, int, uint32 *) __STUB__;
  STEAM_API_BRIDGE_API EBeginAuthSessionResult SteamUser_BeginAuthSession(ISteamUser *, const void *, int, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API void SteamUser_EndAuthSession(ISteamUser *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API void SteamUser_CancelAuthTicket(ISteamUser *, HAuthTicket) __STUB__;
  STEAM_API_BRIDGE_API EUserHasLicenseForAppResult SteamUser_UserHasLicenseForApp(ISteamUser *, CSteamID, AppId_t) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUser_BIsBehindNAT(ISteamUser *) __STUB__;
  STEAM_API_BRIDGE_API void SteamUser_AdvertiseGame(ISteamUser *, CSteamID, uint32, uint16) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUser_RequestEncryptedAppTicket(ISteamUser *, void *, int) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUser_GetEncryptedAppTicket(ISteamUser *, void *, int, uint32 *) __STUB__;

  STEAM_API_BRIDGE_API ISteamFriends *SteamFriends_() __STUB__;
  STEAM_API_BRIDGE_API const char *SteamFriends_GetPersonaName(ISteamFriends *) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_SetPersonaName(ISteamFriends *, const char *) __STUB__;
  STEAM_API_BRIDGE_API EPersonaState SteamFriends_GetPersonaState(ISteamFriends *) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetFriendCount(ISteamFriends *, int) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_GetFriendByIndex(ISteamFriends *, int, int, CSteamID *) __STUB__;
  STEAM_API_BRIDGE_API EFriendRelationship SteamFriends_GetFriendRelationship(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API EPersonaState SteamFriends_GetFriendPersonaState(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamFriends_GetFriendPersonaName(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_GetFriendGamePlayed(ISteamFriends *, CSteamID, FriendGameInfo_t *) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamFriends_GetFriendPersonaNameHistory(ISteamFriends *, CSteamID, int) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_HasFriend(ISteamFriends *, CSteamID, int) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetClanCount(ISteamFriends *) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_GetClanByIndex(ISteamFriends *, int, CSteamID *) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamFriends_GetClanName(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamFriends_GetClanTag(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_GetClanActivityCounts(ISteamFriends *, CSteamID, int *, int *, int *) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_DownloadClanActivityCounts(ISteamFriends *, CSteamID *, int) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetFriendCountFromSource(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API void GetFriendFromSourceByIndex(ISteamFriends *, CSteamID, int, CSteamID *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_IsUserInSource(ISteamFriends *, CSteamID, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_SetInGameVoiceSpeaking(ISteamFriends *, CSteamID, bool) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_ActivateGameOverlay(ISteamFriends *, const char *) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_ActivateGameOverlayToUser(ISteamFriends *, const char *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_ActivateGameOverlayToWebPage(ISteamFriends *, const char *) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_ActivateGameOverlayToStore(ISteamFriends *, AppId_t, EOverlayToStoreFlag) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_SetPlayedWith(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_ActivateGameOverlayInviteDialog(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetSmallFriendAvatar(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetMediumFriendAvatar(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetLargeFriendAvatar(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_RequestUserInformation(ISteamFriends *, CSteamID, bool) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_RequestClanOfficerList(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_GetClanOwner(ISteamFriends *steamFriends, CSteamID, CSteamID *) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetClanOfficerCount(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_GetClanOfficerByIndex(ISteamFriends *, CSteamID, int, CSteamID *) __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamFriends_GetUserRestrictions(ISteamFriends *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_SetRichPresence(ISteamFriends *, const char *, const char *) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_ClearRichPresence(ISteamFriends *) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamFriends_GetFriendRichPresence(ISteamFriends *, CSteamID, const char *) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetFriendRichPresenceKeyCount(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamFriends_GetFriendRichPresenceKeyByIndex(ISteamFriends *, CSteamID, int) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_RequestFriendRichPresence(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_InviteUserToGame(ISteamFriends *, CSteamID, const char *) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetCoplayFriendCount(ISteamFriends *) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_GetCoplayFriend(ISteamFriends *, int, CSteamID *) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetFriendCoplayTime(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API AppId_t SteamFriends_GetFriendCoplayGame(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_JoinClanChatRoom(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_LeaveClanChatRoom(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetClanChatMemberCount(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API void SteamFriends_GetChatMemberByIndex(ISteamFriends *, CSteamID, int, CSteamID *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_SendClanChatMessage(ISteamFriends *, CSteamID, const char *) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetClanChatMessage(ISteamFriends *, CSteamID, int, void *, int, EChatEntryType *, CSteamID *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_IsClanChatAdmin(ISteamFriends *, CSteamID, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_IsClanChatWindowOpenInSteam(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_OpenClanChatWindowInSteam(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_CloseClanChatWindowInSteam(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_SetListenForFriendsMessages(ISteamFriends *, bool) __STUB__;
  STEAM_API_BRIDGE_API bool SteamFriends_ReplyToFriendMessage(ISteamFriends *, CSteamID, const char *) __STUB__;
  STEAM_API_BRIDGE_API int SteamFriends_GetFriendMessage(ISteamFriends *, CSteamID, int, void *, int, EChatEntryType *) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_GetFollowerCount(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_IsFollowing(ISteamFriends *, CSteamID) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamFriends_EnumerateFollowingList(ISteamFriends *, uint32) __STUB__;

  STEAM_API_BRIDGE_API ISteamApps *SteamApps_() __STUB__;
  STEAM_API_BRIDGE_API bool SteamApps_BIsSubscribed(ISteamApps *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamApps_BIsLowViolence(ISteamApps *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamApps_BIsCybercafe(ISteamApps *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamApps_BIsVACBanned(ISteamApps *) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamApps_GetCurrentGameLanguage(ISteamApps *) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamApps_GetAvailableGameLanguages(ISteamApps *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamApps_BIsSubscribedApp(ISteamApps *, AppId_t) __STUB__;
  STEAM_API_BRIDGE_API bool SteamApps_BIsDlcInstalled(ISteamApps *, AppId_t) __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamApps_GetEarliestPurchaseUnixTime(ISteamApps *, AppId_t) __STUB__;
  STEAM_API_BRIDGE_API bool SteamApps_BIsSubscribedFromFreeWeekend(ISteamApps *) __STUB__;
  STEAM_API_BRIDGE_API int SteamApps_GetDLCCount(ISteamApps *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamApps_BGetDLCDataByIndex(ISteamApps *, int, AppId_t *, bool *, char *, int) __STUB__;
  STEAM_API_BRIDGE_API void SteamApps_InstallDLC(ISteamApps *, AppId_t) __STUB__;
  STEAM_API_BRIDGE_API void SteamApps_UninstallDLC(ISteamApps *, AppId_t) __STUB__;
  STEAM_API_BRIDGE_API void SteamApps_RequestAppProofOfPurchaseKey(ISteamApps *, AppId_t) __STUB__;
  STEAM_API_BRIDGE_API bool SteamApps_GetCurrentBetaName(ISteamApps *, char *, int) __STUB__;
  STEAM_API_BRIDGE_API bool SteamApps_MarkContentCorrupt(ISteamApps *, bool) __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamApps_GetInstalledDepots(ISteamApps *, DepotId_t *, uint32) __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamApps_GetAppInstallDir(ISteamApps *, AppId_t, char *, uint32) __STUB__;

  STEAM_API_BRIDGE_API ISteamUserStats *SteamUserStats_() __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_RequestCurrentStats(ISteamUserStats *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetStatI(ISteamUserStats *steamUserStats, const char *pchName, int32 *pData) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetStatF(ISteamUserStats *steamUserStats, const char *pchName, float *pData) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_SetStatI(ISteamUserStats *steamUserStats, const char *pchName, int32 nData) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_SetStatF(ISteamUserStats *steamUserStats, const char *pchName, float fData) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_UpdateAvgRateStat(ISteamUserStats *steamUserStats, const char *pchName, float flCountThisSession, double dSessionLength) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetAchievement(ISteamUserStats *steamUserStats, const char *pchName, bool *pbAchieved) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_SetAchievement(ISteamUserStats *steamUserStats, const char *pchName) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_ClearAchievement(ISteamUserStats *steamUserStats, const char *pchName) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetAchievementAndUnlockTime(ISteamUserStats *steamUserStats, const char *pchName, bool *pbAchieved, uint32 *punUnlockTime) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_StoreStats(ISteamUserStats *steamUserStats) __STUB__;
  STEAM_API_BRIDGE_API int SteamUserStats_GetAchievementIcon(ISteamUserStats *, const char *) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamUserStats_GetAchievementDisplayAttribute(ISteamUserStats *, const char *, const char *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_IndicateAchievementProgress(ISteamUserStats *, const char *, uint32, uint32) __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamUserStats_GetNumAchievements(ISteamUserStats *) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamUserStats_GetAchievementName(ISteamUserStats *steamUserStats, uint32 iAchievement) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_RequestUserStats(ISteamUserStats *steamUserStats, CSteamID steamIDUser) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetUserStatI(ISteamUserStats *, CSteamID, const char *, int32 *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetUserStatF(ISteamUserStats *, CSteamID, const char *, float *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetUserAchievement(ISteamUserStats *, CSteamID, const char *, bool *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetUserAchievementAndUnlockTime(ISteamUserStats *, CSteamID, const char *, bool *, uint32 *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_ResetAllStats(ISteamUserStats *, bool) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_FindOrCreateLeaderboard(ISteamUserStats *, const char *, ELeaderboardSortMethod, ELeaderboardDisplayType) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_FindLeaderboard(ISteamUserStats *, const char *) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamUserStats_GetLeaderboardName(ISteamUserStats *, SteamLeaderboard_t) __STUB__;
  STEAM_API_BRIDGE_API int SteamUserStats_GetLeaderboardEntryCount(ISteamUserStats *, SteamLeaderboard_t) __STUB__;
  STEAM_API_BRIDGE_API ELeaderboardSortMethod SteamUserStats_GetLeaderboardSortMethod(ISteamUserStats *, SteamLeaderboard_t) __STUB__;
  STEAM_API_BRIDGE_API ELeaderboardDisplayType SteamUserStats_GetLeaderboardDisplayType(ISteamUserStats *, SteamLeaderboard_t) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_DownloadLeaderboardEntries(ISteamUserStats *, SteamLeaderboard_t, ELeaderboardDataRequest, int, int) __STUB__
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_DownloadLeaderboardEntriesForUsers(ISteamUserStats *, SteamLeaderboard_t, CSteamID *, int) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetDownloadedLeaderboardEntry(ISteamUserStats *, SteamLeaderboardEntries_t, int, LeaderboardEntry_t *, int32 *, int) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_UploadLeaderboardScore(ISteamUserStats *, SteamLeaderboard_t, ELeaderboardUploadScoreMethod, int32, const int32 *, int) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_AttachLeaderboardUGC(ISteamUserStats *, SteamLeaderboard_t, UGCHandle_t) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_GetNumberOfCurrentPlayers(ISteamUserStats *) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_RequestGlobalAchievementPercentages(ISteamUserStats *) __STUB__;
  STEAM_API_BRIDGE_API int SteamUserStats_GetMostAchievedAchievementInfo(ISteamUserStats *, char *, uint32, float *, bool *) __STUB__;
  STEAM_API_BRIDGE_API int SteamUserStats_GetNextMostAchievedAchievementInfo(ISteamUserStats *, int, char *, uint32, float *, bool *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetAchievementAchievedPercent(ISteamUserStats *, const char *, float *) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUserStats_RequestGlobalStats(ISteamUserStats *, int) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetGlobalStatI(ISteamUserStats *, const char *, int64 *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUserStats_GetGlobalStatD(ISteamUserStats *, const char *, double *) __STUB__;
  STEAM_API_BRIDGE_API int32 SteamUserStats_GetGlobalStatHistoryI(ISteamUserStats *, const char *, int64 *, uint32) __STUB__;
  STEAM_API_BRIDGE_API int32 SteamUserStats_GetGlobalStatHistoryD(ISteamUserStats *, const char *, double *, uint32) __STUB__;

  STEAM_API_BRIDGE_API ISteamUtils *SteamUtils_() __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamUtils_GetSecondsSinceAppActive(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamUtils_GetSecondsSinceComputerActive(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API EUniverse SteamUtils_GetConnectedUniverse(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamUtils_GetServerRealTime(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamUtils_GetIPCountry(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUtils_GetImageSize(ISteamUtils *, int, uint32 *, uint32 *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUtils_GetImageRGBA(ISteamUtils *, int, uint8 *, int) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUtils_GetCSERIPPort(ISteamUtils *, uint32 *, uint16 *) __STUB__;
  STEAM_API_BRIDGE_API uint8 SteamUtils_GetCurrentBatteryPower(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamUtils_GetAppID(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API void SteamUtils_SetOverlayNotificationPosition(ISteamUtils *, ENotificationPosition) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUtils_IsAPICallCompleted(ISteamUtils *, SteamAPICall_t, bool *) __STUB__;
  STEAM_API_BRIDGE_API ESteamAPICallFailure SteamUtils_GetAPICallFailureReason(ISteamUtils *, SteamAPICall_t) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUtils_GetAPICallResult(ISteamUtils *, SteamAPICall_t, void *, int, int, bool *) __STUB__;
  STEAM_API_BRIDGE_API void SteamUtils_RunFrame(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamUtils_GetIPCCallCount(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API void SteamUtils_SetWarningMessageHook(ISteamUtils *, SteamAPIWarningMessageHook_t) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUtils_IsOverlayEnabled(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUtils_BOverlayNeedsPresent(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API SteamAPICall_t SteamUtils_CheckFileSignature(ISteamUtils *, const char *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUtils_ShowGamepadTextInput(ISteamUtils *, EGamepadTextInputMode, EGamepadTextInputLineMode, const char *, uint32) __STUB__;
  STEAM_API_BRIDGE_API uint32 SteamUtils_GetEnteredGamepadTextLength(ISteamUtils *) __STUB__;
  STEAM_API_BRIDGE_API bool SteamUtils_GetEnteredGamepadTextInput(ISteamUtils *, char *, uint32) __STUB__;
  STEAM_API_BRIDGE_API const char *SteamUtils_GetSteamUILanguage(ISteamUtils *) __STUB__;

  STEAM_API_BRIDGE_API const char *steambridge_version_string() __STUB__;
  STEAM_API_BRIDGE_API const char *steambridge_info_string() __STUB__;
}
