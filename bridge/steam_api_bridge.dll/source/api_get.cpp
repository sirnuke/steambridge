// api_get.cpp - Implements various get ISteam*() API calls
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include <dlfcn.h>

#include <steam_api.h>

#define NOMINMAX
#include <wine/debug.h>

#include "api.h"
#include "logging.h"
#include "state.h"

typedef ISteamClient *(*steam_api_SteamClient_t)(void);

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

extern "C"
{

// TODO: Move this guts of this function to state
STEAM_API_BRIDGE_API ISteamClient *SteamClient_()
{
  WINE_TRACE("\n");
  if (!state) __ABORT("NULL internal state (init not called?)");
  __DLSYM_GET(steam_api_SteamClient_t, api, "SteamClient");
  return (*api)();
}

ISteamUser *SteamUser_()
{
  WINE_TRACE("\n");
  if (!state)
  {
    WINE_ERR("NULL internal state (init not called?)\n");
    return NULL;
  }
  return state->getSteamUser();
}

STEAM_API_BRIDGE_API class ISteamFriends *SteamFriends_()
{
  WINE_TRACE("\n");
  if (!state)
  {
    WINE_ERR("NULL internal state (init not called?)\n");
    return NULL;
  }
  return state->getSteamFriends();
}

ISteamApps *SteamApps_()
{
  WINE_TRACE("\n");
  if (!state)
  {
    WINE_ERR("NULL internal state (init not called?)\n");
    return NULL;
  }
  return state->getSteamApps();
}

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

ISteamUtils *SteamUtils_()
{
  WINE_TRACE("\n");
  if (!state)
  {
    WINE_ERR("NULL internal state (init not caled?)\n");
    return NULL;
  }
  return state->getSteamUtils();
}

} // extern "C"

