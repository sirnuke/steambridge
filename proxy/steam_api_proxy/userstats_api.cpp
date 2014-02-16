// userstats_api.cpp - Implements the userstats wrapper and related APIs
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include "stdafx.h"

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "userstats_api.h"
#include "types.h"

#include <steam_api_bridge.h>

#define _THIN_WRAPPER(API, TRACE, ...) { \
  __TRACE("(" TRACE ")", ##__VA_ARGS__); \
  return SteamUserStats_  ##API(steamUserStats, ##__VA_ARGS__); \
}

SteamUserStatsWrapper::SteamUserStatsWrapper() : steamUserStats(NULL)
{
  __TRACE("(this=0x%p)", this);
  steamUserStats = SteamUserStats_();
  __LOG("Wrapping ISteamUserStats (0x%p) in (0x%p)", steamUserStats, this);
}

bool SteamUserStatsWrapper::RequestCurrentStats()
  _THIN_WRAPPER(RequestCurrentStats, "");

bool SteamUserStatsWrapper::GetStat(const char *pchName, int32 *pData)
  _THIN_WRAPPER(GetStatI, "\"%s\",0x%p", pchName, pData)

bool SteamUserStatsWrapper::GetStat(const char *pchName, float *pData)
  _THIN_WRAPPER(GetStatF, "\"%s\",0x%p", pchName, pData)

bool SteamUserStatsWrapper::SetStat(const char *pchName, int32 nData)
  _THIN_WRAPPER(SetStatI, "\"%s\",%u", pchName, nData)

bool SteamUserStatsWrapper::SetStat(const char *pchName, float fData)
  _THIN_WRAPPER(SetStatF, "\"%s\",%f", pchName, fData)

bool SteamUserStatsWrapper::UpdateAvgRateStat(const char *pchName, float flCountThisSession,
    double dSessionLength)
  _THIN_WRAPPER(UpdateAvgRateStat, "\"%s\",%f,%f", pchName, flCountThisSession, dSessionLength)

bool SteamUserStatsWrapper::GetAchievement(const char *pchName, bool *pbAchieved)
  _THIN_WRAPPER(GetAchievement, "\"%s\",0x%p", pchName, pbAchieved)

bool SteamUserStatsWrapper::SetAchievement(const char *pchName)
  _THIN_WRAPPER(SetAchievement, "\"%s\"", pchName)

bool SteamUserStatsWrapper::ClearAchievement(const char *pchName)
  _THIN_WRAPPER(ClearAchievement, "\"%s\"", pchName)

bool SteamUserStatsWrapper::GetAchievementAndUnlockTime(const char *pchName, bool *pbAchieved,
    uint32 *punUnlockTime)
  _THIN_WRAPPER(GetAchievementAndUnlockTime, "\"%s\",0x%p,0x%p", pchName, pbAchieved,
      punUnlockTime)

bool SteamUserStatsWrapper::StoreStats()
  _THIN_WRAPPER(StoreStats, "")

int SteamUserStatsWrapper::GetAchievementIcon(const char *pchName)
  _THIN_WRAPPER(GetAchievementIcon, "\"%s\"", pchName)

const char *SteamUserStatsWrapper::GetAchievementDisplayAttribute(const char *pchName,
    const char *pchKey)
  _THIN_WRAPPER(GetAchievementDisplayAttribute, "\"%s\",\"%s\"", pchName, pchKey)

bool SteamUserStatsWrapper::IndicateAchievementProgress(const char *pchName, uint32 nCurProgress,
    uint32 nMaxProgress)
  _THIN_WRAPPER(IndicateAchievementProgress, "\"%s\",%u,%u", pchName, nCurProgress, nMaxProgress)

uint32 SteamUserStatsWrapper::GetNumAchievements()
  _THIN_WRAPPER(GetNumAchievements, "")

const char *SteamUserStatsWrapper::GetAchievementName(uint32 iAchievement)
  _THIN_WRAPPER(GetAchievementName, "%u", iAchievement)

SteamAPICall_t SteamUserStatsWrapper::RequestUserStats(CSteamID steamIDUser)
  _THIN_WRAPPER(RequestUserStats, "%llu", steamIDUser)

bool SteamUserStatsWrapper::GetUserStat(CSteamID steamIDUser, const char *pchName, int32 *pData)
  _THIN_WRAPPER(GetUserStatI, "%llu,\"%s\",0x%p", steamIDUser, pchName, pData)

bool SteamUserStatsWrapper::GetUserStat(CSteamID steamIDUser, const char *pchName, float *pData)
  _THIN_WRAPPER(GetUserStatF, "%llu,\"%s\",0x%p", steamIDUser, pchName, pData)

bool SteamUserStatsWrapper::GetUserAchievement(CSteamID steamIDUser, const char *pchName,
    bool *pbAchieved)
  _THIN_WRAPPER(GetUserAchievement, "%llu,\"%s\",0x%p", steamIDUser, pchName, pbAchieved)

bool SteamUserStatsWrapper::GetUserAchievementAndUnlockTime(CSteamID steamIDUser,
    const char *pchName, bool *pbAchieved, uint32 *punUnlockTime)
  _THIN_WRAPPER(GetUserAchievementAndUnlockTime, "%llu,\"%s\",0x%p,0x%p", steamIDUser, pchName,
      pbAchieved, punUnlockTime)

bool SteamUserStatsWrapper::ResetAllStats(bool bAchievementsToo)
  _THIN_WRAPPER(ResetAllStats, "%i", bAchievementsToo)

SteamAPICall_t SteamUserStatsWrapper::FindOrCreateLeaderboard(const char *pchLeaderboardName,
    ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType)
  _THIN_WRAPPER(FindOrCreateLeaderboard, "\"%s\",%i,%i", pchLeaderboardName,
      eLeaderboardSortMethod, eLeaderboardDisplayType)

SteamAPICall_t SteamUserStatsWrapper::FindLeaderboard(const char *pchLeaderboardName)
  _THIN_WRAPPER(FindLeaderboard, "\"%s\"", pchLeaderboardName)

const char *SteamUserStatsWrapper::GetLeaderboardName(SteamLeaderboard_t hSteamLeaderboard)
  _THIN_WRAPPER(GetLeaderboardName, "%llu", hSteamLeaderboard)

int SteamUserStatsWrapper::GetLeaderboardEntryCount(SteamLeaderboard_t hSteamLeaderboard)
  _THIN_WRAPPER(GetLeaderboardEntryCount, "%llu", hSteamLeaderboard)

ELeaderboardSortMethod SteamUserStatsWrapper::GetLeaderboardSortMethod(
    SteamLeaderboard_t hSteamLeaderboard)
  _THIN_WRAPPER(GetLeaderboardSortMethod, "%llu", hSteamLeaderboard)

ELeaderboardDisplayType SteamUserStatsWrapper::GetLeaderboardDisplayType(
    SteamLeaderboard_t hSteamLeaderboard)
  _THIN_WRAPPER(GetLeaderboardDisplayType, "%llu", hSteamLeaderboard)

SteamAPICall_t SteamUserStatsWrapper::DownloadLeaderboardEntries(
    SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest,
    int nRangeStart, int nRangeEnd)
  _THIN_WRAPPER(DownloadLeaderboardEntries, "%llu,%i,%i,%i", hSteamLeaderboard,
      eLeaderboardDataRequest, nRangeStart, nRangeEnd)

SteamAPICall_t SteamUserStatsWrapper::DownloadLeaderboardEntriesForUsers(
    SteamLeaderboard_t hSteamLeaderboard, CSteamID *prgUsers, int cUsers)
  _THIN_WRAPPER(DownloadLeaderboardEntriesForUsers, "%llu,0x%p,%i", hSteamLeaderboard, prgUsers,
      cUsers)

bool SteamUserStatsWrapper::GetDownloadedLeaderboardEntry(
    SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index,
    LeaderboardEntry_t *pLeaderboardEntry, int32 *pDetails, int cDetailsMax)
  _THIN_WRAPPER(GetDownloadedLeaderboardEntry, "%llu,%i,%p,%p,%i", hSteamLeaderboardEntries, index,
      pLeaderboardEntry, pDetails, cDetailsMax)

SteamAPICall_t SteamUserStatsWrapper::UploadLeaderboardScore(SteamLeaderboard_t hSteamLeaderboard,
    ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore,
    const int32 *pScoreDetails, int cScoreDetailsCount)
  _THIN_WRAPPER(UploadLeaderboardScore, "%llu,%i,%i,%p,%i", hSteamLeaderboard,
      eLeaderboardUploadScoreMethod, nScore, pScoreDetails, cScoreDetailsCount)

SteamAPICall_t SteamUserStatsWrapper::AttachLeaderboardUGC(SteamLeaderboard_t hSteamLeaderboard,
    UGCHandle_t hUGC)
  _THIN_WRAPPER(AttachLeaderboardUGC, "%llu,%llu", hSteamLeaderboard, hUGC)

SteamAPICall_t SteamUserStatsWrapper::GetNumberOfCurrentPlayers()
  _THIN_WRAPPER(GetNumberOfCurrentPlayers, "")

SteamAPICall_t SteamUserStatsWrapper::RequestGlobalAchievementPercentages()
  _THIN_WRAPPER(RequestGlobalAchievementPercentages, "")

int SteamUserStatsWrapper::GetMostAchievedAchievementInfo(char *pchName, uint32 unNameBufLen,
    float *pflPercent, bool *pbAchieved)
  _THIN_WRAPPER(GetMostAchievedAchievementInfo, "%p,%u,%p,%p", pchName, unNameBufLen, pflPercent,
      pbAchieved)

int SteamUserStatsWrapper::GetNextMostAchievedAchievementInfo(int iIteratorPrevious, char *pchName,
    uint32 unNameBufLen, float *pflPercent, bool *pbAchieved)
  _THIN_WRAPPER(GetNextMostAchievedAchievementInfo, "%i,%p,%u,%p,%p", iIteratorPrevious, pchName,
      unNameBufLen, pflPercent, pbAchieved)

bool SteamUserStatsWrapper::GetAchievementAchievedPercent(const char *pchName, float *pflPercent)
  _THIN_WRAPPER(GetAchievementAchievedPercent, "\"%s\",%p", pchName, pflPercent)

SteamAPICall_t SteamUserStatsWrapper::RequestGlobalStats(int nHistoryDays)
  _THIN_WRAPPER(RequestGlobalStats, "%i", nHistoryDays)

bool SteamUserStatsWrapper::GetGlobalStat(const char *pchStatName, int64 *pData)
  _THIN_WRAPPER(GetGlobalStatI, "\"%s\",%p", pchStatName, pData)

bool SteamUserStatsWrapper::GetGlobalStat(const char *pchStatName, double *pData)
  _THIN_WRAPPER(GetGlobalStatD, "\"%s\",%p", pchStatName, pData)

int32 SteamUserStatsWrapper::GetGlobalStatHistory(const char *pchStatName, int64 *pData,
    uint32 cubData)
  _THIN_WRAPPER(GetGlobalStatHistoryI, "\"%s\",%p,%u", pchStatName, pData, cubData)

int32 SteamUserStatsWrapper::GetGlobalStatHistory(const char *pchStatName, double *pData,
    uint32 cubData)
  _THIN_WRAPPER(GetGlobalStatHistoryD, "\"%s\",%p,%u", pchStatName, pData, cubData)

extern "C"
{
  STEAM_API_PROXY_API void *SteamUserStats()
  {
    __TRACE("()");
    return state.getSteamUserStats();
  }
}

