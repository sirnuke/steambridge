// userstats.cpp - Implements various functions related to ISteamUserStats

#include <cstdio>

#include <steam_api.h>

#define NOMINMAX
#include <windef.h>
#include <winbase.h>
#include <wine/debug.h>

#include "api.h"
#include "core.h"
#include "logging.h"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

extern "C"
{

STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_RequestCurrentStats(
    class ISteamUserStats *steamUserStats)
{
  WINE_TRACE("(0x%p)", steamUserStats);

  if (!steamUserStats)
    __ABORT("NULL steamUserStats pointer!");

  return steamUserStats->RequestCurrentStats();
}

STEAM_API_BRIDGE_API class ISteamUserStats *steam_bridge_SteamUserStats()
{
  WINE_TRACE("()");

  if (!context)
  {
    WINE_WARN("Context is NULL, Init either failed or wasn't called");
    __LOG("Context is NULL, Init either failed or wasn't called");
    return NULL;
  }

  return context->getSteamUserStats();
}

} // extern "C"

