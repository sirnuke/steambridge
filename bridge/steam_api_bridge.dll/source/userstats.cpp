// userstats.cpp - Implements various functions related to ISteamUserStats
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include <cstdio>

#include <steam_api.h>

#define NOMINMAX
#include <wine/debug.h>

#include "api.h"
#include "logging.h"
#include "state.h"

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

class ISteamUserStats;

#define _THIN_WRAPPER(API, TRACE, ...) { \
  WINE_TRACE("(%p," TRACE ")\n", steamUserStats, ##__VA_ARGS__); \
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!"); \
  return steamUserStats->API(__VA_ARGS__); \
}

extern "C"
{

ISteamUserStats *SteamUserStats_()
{
  WINE_TRACE("\n");
  if (!state)
  {
    WINE_ERR("NULL internal context (init not called?)\n");
    return NULL;
  }
  return state->getSteamUserStats();
}

bool SteamUserStats_RequestCurrentStats(ISteamUserStats *steamUserStats)
  _THIN_WRAPPER(RequestCurrentStats, "")

bool SteamUserStats_GetStatI(ISteamUserStats *steamUserStats, const char *pchName, int32 *pData)
  _THIN_WRAPPER(GetStat, "\"%s\",%p", pchName, pData)

bool SteamUserStats_GetStatF(ISteamUserStats *steamUserStats, const char *pchName, float *pData)
  _THIN_WRAPPER(GetStat, "\"%s\",%p", pchName, pData)

bool SteamUserStats_SetStatI(ISteamUserStats *steamUserStats, const char *pchName, int32 nData)
  _THIN_WRAPPER(SetStat, "\"%s\",%i", pchName, nData)

bool SteamUserStats_SetStatF(ISteamUserStats *steamUserStats, const char *pchName, float fData)
  _THIN_WRAPPER(SetStat, "\"%s\",%f", pchName, fData)

bool SteamUserStats_UpdateAvgRateStat(ISteamUserStats *steamUserStats, const char *pchName,
    float flCountThisSession, double dSessionLength)
  _THIN_WRAPPER(UpdateAvgRateStat, "\"%s\",%f,%f", pchName, flCountThisSession, dSessionLength)

bool SteamUserStats_GetAchievement(ISteamUserStats *steamUserStats, const char *pchName,
    bool *pbAchieved)
  _THIN_WRAPPER(GetAchievement, "\"%s\",%p", pchName, pbAchieved)

bool SteamUserStats_SetAchievement(ISteamUserStats *steamUserStats, const char *pchName)
  _THIN_WRAPPER(SetAchievement, "\"%s\"", pchName)

bool SteamUserStats_ClearAchievement(ISteamUserStats *steamUserStats, const char *pchName)
  _THIN_WRAPPER(ClearAchievement, "\"%s\"", pchName)

bool SteamUserStats_GetAchievementAndUnlockTime(ISteamUserStats *steamUserStats,
    const char *pchName, bool *pbAchieved, uint32 *punUnlockTime)
  _THIN_WRAPPER(GetAchievementAndUnlockTime, "\"%s\",%p,%p", pchName, pbAchieved, punUnlockTime)

bool SteamUserStats_StoreStats(ISteamUserStats *steamUserStats)
  _THIN_WRAPPER(StoreStats, "")

int SteamUserStats_GetAchievementIcon(ISteamUserStats *steamUserStats, const char *pchName)
  _THIN_WRAPPER(GetAchievementIcon, "\"%s\"", pchName)

const char *SteamUserStats_GetAchievementDisplayAttribute(ISteamUserStats *steamUserStats,
    const char *pchName, const char *pchKey)
  _THIN_WRAPPER(GetAchievementDisplayAttribute, "\"%s\",\"%s\"", pchName, pchKey)

bool SteamUserStats_IndicateAchievementProgress(ISteamUserStats *steamUserStats,
    const char *pchName, uint32 nCurProgress, uint32 nMaxProgress)
  _THIN_WRAPPER(IndicateAchievementProgress, "\"%s\",%u,%u", pchName, nCurProgress, nMaxProgress)

uint32 SteamUserStats_GetNumAchievements(ISteamUserStats *steamUserStats)
  _THIN_WRAPPER(GetNumAchievements, "")

const char *SteamUserStats_GetAchievementName(ISteamUserStats *steamUserStats, uint32 iAchievement)
  _THIN_WRAPPER(GetAchievementName, "%u", iAchievement)

SteamAPICall_t SteamUserStats_RequestUserStats(ISteamUserStats *steamUserStats,
    CSteamID steamIDUser)
  _THIN_WRAPPER(RequestUserStats, "%llu", steamIDUser)

bool SteamUserStats_GetUserStatI(ISteamUserStats *steamUserStats, CSteamID steamIDUser,
    const char *pchName, int32 *pData)
  _THIN_WRAPPER(GetUserStat, "%llu,\"%s\",%p", steamIDUser, pchName, pData)

bool SteamUserStats_GetUserStatF(ISteamUserStats *steamUserStats, CSteamID steamIDUser,
    const char *pchName, float *pData)
  _THIN_WRAPPER(GetUserStat, "%llu,\"%s\",%p", steamIDUser, pchName, pData)

bool SteamUserStats_GetUserAchievement(ISteamUserStats *steamUserStats, CSteamID steamIDUser,
    const char *pchName, bool *pbAchieved)
  _THIN_WRAPPER(GetUserAchievement, "%llu,\"%s\",%p", steamIDUser, pchName, pbAchieved)

bool SteamUserStats_GetUserAchievementAndUnlockTime(ISteamUserStats *steamUserStats,
    CSteamID steamIDUser, const char *pchName, bool *pbAchieved, uint32 *punUnlockTime)
  _THIN_WRAPPER(GetUserAchievementAndUnlockTime, "%llu,\"%s\",%p,%p", steamIDUser, pchName,
      pbAchieved, punUnlockTime)

bool SteamUserStats_ResetAllStats(ISteamUserStats *steamUserStats, bool bAchievementsToo)
  _THIN_WRAPPER(ResetAllStats, "%i", bAchievementsToo)

SteamAPICall_t SteamUserStats_FindOrCreateLeaderboard(ISteamUserStats *steamUserStats,
    const char *pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod,
    ELeaderboardDisplayType eLeaderboardDisplayType)
  _THIN_WRAPPER(FindOrCreateLeaderboard, "\"%s\",%i,%i", pchLeaderboardName, eLeaderboardSortMethod,
      eLeaderboardDisplayType)

SteamAPICall_t SteamUserStats_FindLeaderboard(ISteamUserStats *steamUserStats,
    const char *pchLeaderboardName)
  _THIN_WRAPPER(FindLeaderboard, "\"%s\"", pchLeaderboardName)

const char *SteamUserStats_GetLeaderboardName(ISteamUserStats *steamUserStats,
    SteamLeaderboard_t hSteamLeaderboard)
  _THIN_WRAPPER(GetLeaderboardName, "%llu", hSteamLeaderboard)

int SteamUserStats_GetLeaderboardEntryCount(ISteamUserStats *steamUserStats,
    SteamLeaderboard_t hSteamLeaderboard)
  _THIN_WRAPPER(GetLeaderboardEntryCount, "%llu", hSteamLeaderboard)

ELeaderboardSortMethod SteamUserStats_GetLeaderboardSortMethod(ISteamUserStats *steamUserStats,
    SteamLeaderboard_t hSteamLeaderboard)
  _THIN_WRAPPER(GetLeaderboardSortMethod, "%llu", hSteamLeaderboard)

ELeaderboardDisplayType SteamUserStats_GetLeaderboardDisplayType(ISteamUserStats *steamUserStats, 
    SteamLeaderboard_t hSteamLeaderboard)
  _THIN_WRAPPER(GetLeaderboardDisplayType, "%llu", hSteamLeaderboard)

SteamAPICall_t SteamUserStats_DownloadLeaderboardEntries(ISteamUserStats *steamUserStats,
    SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest,
    int nRangeStart, int nRangeEnd)
  _THIN_WRAPPER(DownloadLeaderboardEntries, "%llu,%i,%i,%i", hSteamLeaderboard,
      eLeaderboardDataRequest, nRangeStart, nRangeEnd)

SteamAPICall_t SteamUserStats_DownloadLeaderboardEntriesForUsers(ISteamUserStats *steamUserStats,
    SteamLeaderboard_t hSteamLeaderboard, CSteamID *prgUsers, int cUsers)
  _THIN_WRAPPER(DownloadLeaderboardEntriesForUsers, "%llu,%p,%i", hSteamLeaderboard, prgUsers,
      cUsers)

bool SteamUserStats_GetDownloadedLeaderboardEntry(ISteamUserStats *steamUserStats,
    SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index,
    LeaderboardEntry_t *pLeaderboardEntry, int32 *pDetails, int cDetailsMax)
  _THIN_WRAPPER(GetDownloadedLeaderboardEntry, "%llu,%i,%p,%p,%i", hSteamLeaderboardEntries, index,
      pLeaderboardEntry, pDetails, cDetailsMax)

SteamAPICall_t SteamUserStats_UploadLeaderboardScore(ISteamUserStats *steamUserStats,
    SteamLeaderboard_t hSteamLeaderboard,
    ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore,
    const int32 *pScoreDetails, int cScoreDetailsCount)
  _THIN_WRAPPER(UploadLeaderboardScore, "%llu,%i,%i,%p,%i", hSteamLeaderboard,
      eLeaderboardUploadScoreMethod, nScore, pScoreDetails, cScoreDetailsCount)

SteamAPICall_t SteamUserStats_AttachLeaderboardUGC(ISteamUserStats *steamUserStats,
    SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC)
  _THIN_WRAPPER(AttachLeaderboardUGC, "%llu,%llu", hSteamLeaderboard, hUGC)

SteamAPICall_t SteamUserStats_GetNumberOfCurrentPlayers(ISteamUserStats *steamUserStats)
  _THIN_WRAPPER(GetNumberOfCurrentPlayers, "")

SteamAPICall_t SteamUserStats_RequestGlobalAchievementPercentages(ISteamUserStats *steamUserStats)
  _THIN_WRAPPER(RequestGlobalAchievementPercentages, "")

int SteamUserStats_GetMostAchievedAchievementInfo(ISteamUserStats *steamUserStats, char *pchName,
    uint32 unNameBufLen, float *pflPercent, bool *pbAchieved)
  _THIN_WRAPPER(GetMostAchievedAchievementInfo, "%p,%u,%p,%p", pchName, unNameBufLen, pflPercent,
      pbAchieved)

int SteamUserStats_GetNextMostAchievedAchievementInfo(ISteamUserStats *steamUserStats,
    int iIteratorPrevious, char *pchName, uint32 unNameBufLen, float *pflPercent, bool *pbAchieved)
  _THIN_WRAPPER(GetNextMostAchievedAchievementInfo, "%i,%p,%i,%p,%p", iIteratorPrevious, pchName,
      unNameBufLen, pflPercent, pbAchieved)

bool SteamUserStats_GetAchievementAchievedPercent(ISteamUserStats *steamUserStats,
    const char *pchName, float *pflPercent)
  _THIN_WRAPPER(GetAchievementAchievedPercent, "\"%s\",%p", pchName, pflPercent)

SteamAPICall_t SteamUserStats_RequestGlobalStats(ISteamUserStats *steamUserStats, int nHistoryDays)
  _THIN_WRAPPER(RequestGlobalStats, "%i", nHistoryDays)

bool SteamUserStats_GetGlobalStatI(ISteamUserStats *steamUserStats, const char *pchStatName,
    int64 *pData)
  _THIN_WRAPPER(GetGlobalStat, "\"%s\",%p", pchStatName, pData)

bool SteamUserStats_GetGlobalStatD(ISteamUserStats *steamUserStats, const char *pchStatName,
    double *pData)
  _THIN_WRAPPER(GetGlobalStat, "\"%s\",%p", pchStatName, pData)

int32 SteamUserStats_GetGlobalStatHistoryI(ISteamUserStats *steamUserStats, const char *pchStatName,
    int64 *pData, uint32 cubData)
  _THIN_WRAPPER(GetGlobalStatHistory, "\"%s\",%p,%u", pchStatName, pData, cubData)

int32 SteamUserStats_GetGlobalStatHistoryD(ISteamUserStats *steamUserStats, const char *pchStatName,
    double *pData, uint32 cubData)
  _THIN_WRAPPER(GetGlobalStatHistory, "\"%s\",%p,%u", pchStatName, pData, cubData)

} // extern "C"

