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
  STEAM_API_BRIDGE_API int steam_bridge_SteamAPI_RegisterCallback(steam_bridge_CallbackRunFunc, steam_bridge_CallbackRunArgsFunc, void *, int, int) __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_UnregisterCallback(void *) __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_RunCallbacks() __STUB__;

  STEAM_API_BRIDGE_API ISteamClient *steam_bridge_SteamClient() __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamClient_SetWarningMessageHook(ISteamClient *, SteamAPIWarningMessageHook_t) __STUB__;

  STEAM_API_BRIDGE_API ISteamUser *steam_bridge_SteamUser() __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamUser_GetSteamID(ISteamUser *, CSteamID *) __STUB__;
  STEAM_API_BRIDGE_API bool steam_bridge_SteamUser_BLoggedOn(ISteamUser *) __STUB__;
  STEAM_API_BRIDGE_API int steam_bridge_SteamUser_InitiateGameConnection(ISteamUser *, void *, int, CSteamID, uint32, uint16, bool) __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamUser_TerminateGameConnection(ISteamUser *, uint32, uint16) __STUB__;

  STEAM_API_BRIDGE_API ISteamFriends *steam_bridge_SteamFriends() __STUB__;
  STEAM_API_BRIDGE_API const char *steam_bridge_SteamFriends_GetPersonaName(ISteamFriends *) __STUB__;
  STEAM_API_BRIDGE_API int steam_bridge_SteamFriends_GetFriendCount(ISteamFriends *, int) __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamFriends_SetPlayedWith(ISteamFriends *, CSteamID) __STUB__;

  STEAM_API_BRIDGE_API ISteamApps *steam_bridge_SteamApps() __STUB__;
  STEAM_API_BRIDGE_API bool steam_bridge_SteamApps_BIsSubscribedApp(ISteamApps *, AppId_t) __STUB__;
  STEAM_API_BRIDGE_API const char *steam_bridge_SteamApps_GetCurrentGameLanguage(ISteamApps *) __STUB__;

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

  STEAM_API_BRIDGE_API ISteamUtils *steam_bridge_SteamUtils() __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamUtils_SetOverlayNotificationPosition(ISteamUtils *, int) __STUB__;

  STEAM_API_BRIDGE_API const char *steam_bridge_version_string() __STUB__;
  STEAM_API_BRIDGE_API const char *steam_bridge_info_string() __STUB__;
}
