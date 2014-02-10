// friends.cpp - Implements various functions related to the ISteamFriends class.

#include <cstdio>

#include <steam_api.h>

#define NOMINMAX
#include <wine/debug.h>

#include "api.h"
#include "core.h"
#include "logging.h"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

extern "C"
{

STEAM_API_BRIDGE_API bool steam_bridge_SteamApps_BIsSubscribedApp(
    class ISteamApps *steamApps, AppId_t appId)
{
  WINE_TRACE("(0x%p,%u)", steamApps, appId);

  if (!steamApps)
    __ABORT("NULL steamApps pointer!");

  return steamApps->BIsSubscribedApp(appId);
}

STEAM_API_BRIDGE_API const char *steam_bridge_SteamApps_GetCurrentGameLanguage(
    class ISteamApps *steamApps)
{
  WINE_TRACE("(0x%p)", steamApps);

  if (!steamApps)
    __ABORT("NULL steamApps pointer!");

  return steamApps->GetCurrentGameLanguage();
}

STEAM_API_BRIDGE_API class ISteamApps *steam_bridge_SteamApps()
{
  WINE_TRACE("()");

  if (!context)
  {
    WINE_ERR("Context is NULL, Init either failed or wasn't called\n");
    return NULL;
  }

  return context->getSteamApps();
}

} // extern "C"

