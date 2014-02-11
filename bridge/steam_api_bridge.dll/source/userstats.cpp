// userstats.cpp - Implements various functions related to ISteamUserStats

#include <cstdio>

#include <steam_api.h>

#define NOMINMAX
#include <wine/debug.h>

#include "api.h"
#include "logging.h"
#include "state.h"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

extern "C"
{

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_RequestCurrentStats(
    class ISteamUserStats *steamUserStats)
{
  WINE_TRACE("(%p)\n", steamUserStats);

  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");

  return steamUserStats->RequestCurrentStats();
}

STEAM_API_BRIDGE_API uint32 steam_bridge_SteamUserStats_GetNumAchievements(
    ISteamUserStats *steamUserStats)
{
  WINE_TRACE("(%p)\n", steamUserStats);

  if (!steamUserStats) __ABORT("NULL steamUserStats pointer!");

  return steamUserStats->GetNumAchievements();
}

STEAM_API_BRIDGE_API class ISteamUserStats *steam_bridge_SteamUserStats()
{
  WINE_TRACE("\n");

  if (!state)
  {
    WINE_ERR("NULL internal context (init not called?)\n");
    return NULL;
  }

  return state->getSteamUserStats();
}

} // extern "C"

