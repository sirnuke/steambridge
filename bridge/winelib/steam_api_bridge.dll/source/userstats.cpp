// userstats.cpp - Implements various functions related to ISteamUserStats

#include <cstdio>

#include <steam_api.h>

#include <windef.h>
#include <winbase.h>
#include <wine/debug.h>

#include "api.h"
#include "core.h"
#include "logging.h"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

extern "C"
{

STEAM_API_BRIDGE_API class ISteamUserStats *steam_bridge_SteamUserStats()
{
  WINE_TRACE("()");

  if (!context)
  {
    WINE_WARN("Context is NULL, Init either failed or wasn't called");
    return NULL;
  }

  return context->getSteamUserStats();
}

} // extern "C"

