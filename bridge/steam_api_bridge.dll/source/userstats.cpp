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

STEAM_API_BRIDGE_API uint32 steam_bridge_SteamUserStats_GetNumAchievements(
    ISteamUserStats *steamUserStats)
{
  WINE_TRACE("(%p)\n", steamUserStats);
  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");
  return steamUserStats->GetNumAchievements();
}

} // extern "C"

