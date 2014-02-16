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

SteamUserStatsWrapper::SteamUserStatsWrapper() : steamUserStats(NULL)
{
  __TRACE("(this=0x%p)", this);
  steamUserStats = steam_bridge_SteamUserStats();
  __LOG("Wrapping ISteamUserStats (0x%p) in (0x%p)", steamUserStats, this);
}

bool SteamUserStatsWrapper::RequestCurrentStats()
{
  __TRACE("()");
  return steam_bridge_SteamUserStats_RequestCurrentStats(steamUserStats);
}

bool SteamUserStatsWrapper::GetStat(const char *pchName, int32 *pData)
{
  __TRACE("(\"%s\",%p)", pchName, pData);
  return steam_bridge_SteamUserStats_GetStatI(steamUserStats, pchName, pData);
}


bool SteamUserStatsWrapper::GetStat(const char *pchName, float *pData)
{
  __TRACE("(\"%s\",%p)", pchName, pData);
  return steam_bridge_SteamUserStats_GetStatF(steamUserStats, pchName, pData);
}

bool SteamUserStatsWrapper::SetStat(const char *pchName, int32 nData)
{
  __TRACE("(\"%s\",%i)", pchName, nData);
  return steam_bridge_SteamUserStats_SetStatI(steamUserStats, pchName, nData);
}

bool SteamUserStatsWrapper::SetStat(const char *pchName, float fData)
{
  __TRACE("(\"%s\",%i)", pchName, fData);
  return steam_bridge_SteamUserStats_SetStatF(steamUserStats, pchName, fData);
}

bool SteamUserStatsWrapper::UpdateAvgRateStat(const char *pchName,
    float flCountThisSession, double dSessionLength)
{
  __TRACE("(\"%s\",%f,%f)", pchName, flCountThisSession, dSessionLength);
  return steam_bridge_SteamUserStats_UpdateAvgRateStat(steamUserStats, pchName,
    flCountThisSession, dSessionLength);
}

bool SteamUserStatsWrapper::GetAchievement(const char *pchName,
  bool *pbAchieved)
{
  __TRACE("(\"%s\",%p)", pchName, pbAchieved);
  return steam_bridge_SteamUserStats_GetAchievement(steamUserStats, pchName,
    pbAchieved);
}

bool SteamUserStatsWrapper::SetAchievement(const char *pchName)
{
  __TRACE("(\"%s\")", pchName);
  return steam_bridge_SteamUserStats_SetAchievement(steamUserStats, pchName);
}

bool SteamUserStatsWrapper::ClearAchievement(const char *pchName)
{
  __TRACE("(\"%s\")", pchName);
  return steam_bridge_SteamUserStats_ClearAchievement(steamUserStats, pchName);
}

bool SteamUserStatsWrapper::GetAchievementAndUnlockTime(const char *pchName,
    bool *pbAchieved, uint32 *punUnlockTime)
{
  __TRACE("(\"%s\",%p,%p)", pchName, pbAchieved, punUnlockTime);
  return steam_bridge_SteamUserStats_GetAchievementAndUnlockTime(
    steamUserStats, pchName, pbAchieved, punUnlockTime);
}

bool SteamUserStatsWrapper::StoreStats()
{
  __TRACE("()");
  return steam_bridge_SteamUserStats_StoreStats(steamUserStats);
}

int SteamUserStatsWrapper::GetAchievementIcon(const char *pchName)
  __STUB("(\"%s\")", pchName)

const char *SteamUserStatsWrapper::GetAchievementDisplayAttribute(
    const char *pchName, const char *pchKey)
  __STUB("(\"%s\",\"%s\")", pchName, pchKey)

bool SteamUserStatsWrapper::IndicateAchievementProgress(const char *pchName,
    uint32 nCurProgress, uint32 nMaxProgress)
  __STUB("(\"%s\",%u,%u)", pchName, nCurProgress, nMaxProgress)

uint32 SteamUserStatsWrapper::GetNumAchievements()
{
  __TRACE("()");
  return steam_bridge_SteamUserStats_GetNumAchievements(steamUserStats);
}

const char *SteamUserStatsWrapper::GetAchievementName(uint32 iAchievement)
  __STUB("(%u)", iAchievement)

SteamAPICall_t SteamUserStatsWrapper::RequestUserStats(uint64 steamIDUser)
  __STUB("(%lu)", steamIDUser)

bool SteamUserStatsWrapper::GetUserStat(uint64 steamIDUser,
    const char *pchName, int32 *pData)
  __STUB("(%lu,\"%s\",0x%p)", steamIDUser, pchName, pData)

bool SteamUserStatsWrapper::GetUserStat(uint64 steamIDUser,
    const char *pchName, float *pData)
  __STUB("(%lu,\"%s\",0x%p)", steamIDUser, pchName, pData)

bool SteamUserStatsWrapper::GetUserAchievement(uint64 steamIDUser,
    const char *pchName, bool *pbAchieved)
  __STUB("(%lu,\"%s\",0x%p)", steamIDUser, pchName, pbAchieved)

bool SteamUserStatsWrapper::GetUserAchievementAndUnlockTime(uint64 steamIDUser,
    const char *pchName, bool *pbAchieved, uint32 *punUnlockTime)
  __STUB("(%lu,\"%s\",0x%p,0x%p)", steamIDUser, pchName, pbAchieved,
      punUnlockTime)

bool SteamUserStatsWrapper::ResetAllStats(bool bAchievementsToo)
  __STUB("(%i)", bAchievementsToo)

SteamAPICall_t SteamUserStatsWrapper::FindOrCreateLeaderboard(
    const char *pchLeaderboardName, int eLeaderboardSortMethod,
    int eLeaderboardDisplayType)
  __STUB("(\"%s\",%i,%i)", pchLeaderboardName, eLeaderboardSortMethod,
      eLeaderboardDisplayType)

SteamAPICall_t SteamUserStatsWrapper::FindLeaderboard(
    const char *pchLeaderboardName)
  __STUB("(\"%s\")", pchLeaderboardName)

const char *SteamUserStatsWrapper::GetLeaderboardName(
    SteamLeaderboard_t hSteamLeaderboard)
  __STUB("(%lu)", hSteamLeaderboard)

int SteamUserStatsWrapper::GetLeaderboardEntryCount(
    SteamLeaderboard_t hSteamLeaderboard)
  __STUB("(%lu)", hSteamLeaderboard)

int SteamUserStatsWrapper::GetLeaderboardSortMethod(
    SteamLeaderboard_t hSteamLeaderboard)
  __STUB("(%lu)", hSteamLeaderboard)

int SteamUserStatsWrapper::GetLeaderboardDisplayType(
    SteamLeaderboard_t hSteamLeaderboard)
  __STUB("(%lu)", hSteamLeaderboard)

SteamAPICall_t SteamUserStatsWrapper::DownloadLeaderboardEntries(
    SteamLeaderboard_t hSteamLeaderboard, int eLeaderboardDataRequest,
    int nRangeStart, int nRangeEnd)
  __STUB("(%lu,%i,%i,%i)", hSteamLeaderboard, eLeaderboardDataRequest,
      nRangeStart, nRangeEnd)

SteamAPICall_t SteamUserStatsWrapper::DownloadLeaderboardEntriesForUsers(
    SteamLeaderboard_t hSteamLeaderboard, uint64 *prgUsers, int cUsers)
  __STUB("(%lu,0x%p,%i)", hSteamLeaderboard, prgUsers, cUsers)

bool SteamUserStatsWrapper::GetDownloadedLeaderboardEntry(
    SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index,
    LeaderboardEntry_t *pLeaderboardEntry, int32 *pDetails, int cDetailsMax)
  __STUB("(%lu,%i,0x%p,0x%p,%i)", hSteamLeaderboardEntries, index,
      pLeaderboardEntry, pDetails, cDetailsMax)

SteamAPICall_t SteamUserStatsWrapper::UploadLeaderboardScore(
    SteamLeaderboard_t hSteamLeaderboard, int eLeaderboardUploadScoreMethod,
    int32 nScore, const int32 *pScoreDetails, int cScoreDetailsCount)
  __STUB("(%lu,%i,%i,0x%p,%i)", hSteamLeaderboard,
      eLeaderboardUploadScoreMethod, nScore, pScoreDetails, cScoreDetailsCount)

SteamAPICall_t SteamUserStatsWrapper::AttachLeaderboardUGC(
    SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC)
  __STUB("(%lu,%lu)", hSteamLeaderboard, hUGC)

SteamAPICall_t SteamUserStatsWrapper::GetNumberOfCurrentPlayers()
  __STUB("")

SteamAPICall_t SteamUserStatsWrapper::RequestGlobalAchievementPercentages()
  __STUB("")

int SteamUserStatsWrapper::GetMostAchievedAchievementInfo(char *pchName,
    uint32 unNameBufLen, float *pflPercent, bool *pbAchieved)
  __STUB("(0x%p,%u,0x%p,0x%p)", pchName, unNameBufLen, pflPercent,
      pbAchieved)

int SteamUserStatsWrapper::GetNextMostAchievedAchievementInfo(
    int iIteratorPrevious, char *pchName, uint32 unNameBufLen,
    float *pflPercent, bool *pbAchieved)
  __STUB("(%i,0x%p,%u,0x%p,0x%p)", iIteratorPrevious, pchName, unNameBufLen,
      pflPercent, pbAchieved)

bool SteamUserStatsWrapper::GetAchievementAchievedPercent(const char *pchName,
    float *pflPercent)
  __STUB("(\"%s\",0x%p)", pchName, pflPercent)

SteamAPICall_t SteamUserStatsWrapper::RequestGlobalStats(int nHistoryDays)
  __STUB("(%i)", nHistoryDays)

bool SteamUserStatsWrapper::GetGlobalStat(const char *pchStatName, int64 *pData)
  __STUB("(\"%s\",0x%p)", pchStatName, pData)

bool SteamUserStatsWrapper::GetGlobalStat(const char *pchStatName,
    double *pData)
  __STUB("(\"%s\",0x%p)", pchStatName, pData)

int32 SteamUserStatsWrapper::GetGlobalStatHistory(const char *pchStatName,
    int64 *pData, uint32 cubData)
  __STUB("(\"%s\",0x%p,%u)", pchStatName, pData, cubData)

int32 SteamUserStatsWrapper::GetGlobalStatHistory(const char *pchStatName,
    double *pData, uint32 cubData)
  __STUB("(\"%s\",0x%p,%u)", pchStatName, pData, cubData)

extern "C"
{
  STEAM_API_PROXY_API void *SteamUserStats()
  {
    __TRACE("()");
    return state.getSteamUserStats();
  }
}

