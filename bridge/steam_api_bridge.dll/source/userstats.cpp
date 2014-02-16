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

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

class ISteamUserStats;

#define _THIN_WRAPPER(API, TRACE, ...) { \
  WINE_TRACE("(%p," TRACE ")\n", steamUserStats, ##__VA_ARGS__); \
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!"); \
  return steamUserStats->API(__VA_ARGS__); \
}

extern "C"
{

ISteamUserStats *SteamUserStatsObj()
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

} // extern "C"

