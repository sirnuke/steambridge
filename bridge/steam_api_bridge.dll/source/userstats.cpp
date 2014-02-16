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

#define _THIN_WRAPPER(TRACE, API, ...) { \
  WINE_TRACE(TRACE, steamUserStats, ##__VA_ARGS__); \
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!"); \
  return steamUserStats->API(__VA_ARGS__); \
}

extern "C"
{

STEAM_API_BRIDGE_API ISteamUserStats *steam_bridge_SteamUserStats()
{
  WINE_TRACE("\n");

  if (!state)
  {
    WINE_ERR("NULL internal context (init not called?)\n");
    return NULL;
  }

  return state->getSteamUserStats();
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_RequestCurrentStats(
    ISteamUserStats *steamUserStats)
{
  WINE_TRACE("(%p)\n", steamUserStats);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->RequestCurrentStats();
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_GetStatI(
    ISteamUserStats *steamUserStats, const char *pchName, int32 *pData)
{
  WINE_TRACE("(%p,\"%s\",%p)\n", steamUserStats, pchName, pData);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetStat(pchName, pData);
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_GetStatF(
    ISteamUserStats *steamUserStats, const char *pchName, float *pData)
{
  WINE_TRACE("(%p,\"%s\",%p)\n", steamUserStats, pchName, pData);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetStat(pchName, pData);
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_SetStatI(
    ISteamUserStats *steamUserStats, const char *pchName, int32 nData)
{
  WINE_TRACE("(%p,\"%s\",%i)\n", steamUserStats, pchName, nData);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->SetStat(pchName, nData);
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_SetStatF(
    ISteamUserStats *steamUserStats, const char *pchName, float fData)
{
  WINE_TRACE("(%p,\"%s\",%f)\n", steamUserStats, pchName, fData);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->SetStat(pchName, fData);
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_UpdateAvgRateStat(
    ISteamUserStats *steamUserStats, const char *pchName,
    float flCountThisSession, double dSessionLength)
{
  WINE_TRACE("(%p,\"%s\",%f,%f)\n", steamUserStats, pchName, flCountThisSession,
      dSessionLength);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->UpdateAvgRateStat(pchName, flCountThisSession,
      dSessionLength);
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_GetAchievement(
    ISteamUserStats *steamUserStats, const char *pchName, bool *pbAchieved)
{
  WINE_TRACE("(%p,\"%s\",%p)\n", steamUserStats, pchName, pbAchieved);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetAchievement(pchName, pbAchieved);
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_SetAchievement(
    ISteamUserStats *steamUserStats, const char *pchName)
{
  WINE_TRACE("(%p,\"%s\")\n", steamUserStats, pchName);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->SetAchievement(pchName);
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_ClearAchievement(
    ISteamUserStats *steamUserStats, const char *pchName)
{
  WINE_TRACE("(%p,\"%s\")\n", steamUserStats, pchName);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->ClearAchievement(pchName);
}

STEAM_API_BRIDGE_API bool
  steam_bridge_SteamUserStats_GetAchievementAndUnlockTime(
    ISteamUserStats *steamUserStats, const char *pchName, bool *pbAchieved,
    uint32 *punUnlockTime)
{
  WINE_TRACE("(%p,\"%s\",%p,%p)\n", steamUserStats, pchName, pbAchieved,
      punUnlockTime);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetAchievementAndUnlockTime(pchName, pbAchieved,
      punUnlockTime);
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_StoreStats(
    ISteamUserStats *steamUserStats)
{
  WINE_TRACE("(%p)\n", steamUserStats);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->StoreStats();
}

STEAM_API_BRIDGE_API int steam_bridge_SteamUserStats_GetAchievementIcon(
    ISteamUserStats *steamUserStats, const char *pchName)
{
  WINE_TRACE("(%p,\"%s\")\n", steamUserStats, pchName);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetAchievementIcon(pchName);
}

// TODO: Does this function work right?  As I understand, wide-strings
//       are weird between Windows and Linux, but normal cstrings should
//       be fine.
STEAM_API_BRIDGE_API const char *
  steam_bridge_SteamUserStats_GetAchievementDisplayAttribute(
    ISteamUserStats *steamUserStats, const char *pchName, const char *pchKey)
{
  WINE_TRACE("(%p,\"%s\",\"%s\")\n", steamUserStats, pchName, pchKey);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetAchievementDisplayAttribute(pchName, pchKey);
}

STEAM_API_BRIDGE_API bool 
  steam_bridge_SteamUserStats_IndicateAchievementProgress(
    ISteamUserStats *steamUserStats, const char *pchName, uint32 nCurProgress,
    uint32 nMaxProgress)
{
  WINE_TRACE("(%p,\"%s\",%u,%u)", steamUserStats, pchName, nCurProgress,
      nMaxProgress);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->IndicateAchievementProgress(pchName, nCurProgress,
      nMaxProgress);
}

STEAM_API_BRIDGE_API uint32 steam_bridge_SteamUserStats_GetNumAchievements(
    ISteamUserStats *steamUserStats)
{
  WINE_TRACE("(%p)\n", steamUserStats);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetNumAchievements();
}

STEAM_API_BRIDGE_API const char *steam_bridge_SteamUserStats_GetAchievementName(
    ISteamUserStats *steamUserStats, uint32 iAchievement)
{
  WINE_TRACE("(%p,%u)\n");
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetAchievementName(iAchievement);
}

STEAM_API_BRIDGE_API SteamAPICall_t
  steam_bridge_SteamUserStats_RequestUserStats(ISteamUserStats *steamUserStats,
      CSteamID steamIDUser)
{
  WINE_TRACE("(%p,%llu)\n", steamUserStats, steamIDUser);
  //WINE_TRACE("(%p,%llu)\n", steamUserStats, steamIDUser.ConvertToUint64());
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->RequestUserStats(steamIDUser);
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_GetUserStatI(
    ISteamUserStats *steamUserStats, CSteamID steamIDUser, const char *pchName,
    int32 *pData)
{
  WINE_TRACE("(%p,%llu,\"%s\",%p)\n", steamUserStats,
      steamIDUser.ConvertToUint64(), pchName);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetUserStat(steamIDUser, pchName, pData);
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_GetUserStatF(
    ISteamUserStats *steamUserStats, CSteamID steamIDUser, const char *pchName,
    float *pData)
{
  WINE_TRACE("(%p,%llu,\"%s\",%p)\n", steamUserStats,
      steamIDUser.ConvertToUint64(), pchName, pData);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetUserStat(steamIDUser, pchName, pData);
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_GetUserAchievement(
    ISteamUserStats *steamUserStats, CSteamID steamIDUser, const char *pchName,
    bool *pbAchieved)
{
  WINE_TRACE("(%p,%llu,\"%s\",%p)\n", steamUserStats,
      steamIDUser.ConvertToUint64(), pchName, pbAchieved);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetUserAchievement(steamIDUser, pchName, pbAchieved);
}

STEAM_API_BRIDGE_API bool 
  steam_bridge_SteamUserStats_GetUserAchievementAndUnlockTime(
    ISteamUserStats *steamUserStats, CSteamID steamIDUser, const char *pchName,
    bool *pbAchieved, uint32 *punUnlockTime)
  _THIN_WRAPPER("(%p,%llu,\"%s\",%p,%p)\n", GetUserAchievementAndUnlockTime,
      steamIDUser, pchName, pbAchieved, punUnlockTime)

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_ResetAllStats(
    ISteamUserStats *steamUserStats, bool bAchievementsToo)
  _THIN_WRAPPER("(%p,%i)\n", ResetAllStats, bAchievementsToo)
} // extern "C"

