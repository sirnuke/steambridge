// api_get.cpp - Implements various get ISteam*() API calls
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include <steam_api.h>

#define NOMINMAX
#include <wine/debug.h>

#include "api.h"
#include "logging.h"
#include "state.h"

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

extern "C"
{

STEAM_API_BRIDGE_API ISteamClient *SteamClient_()
{
  WINE_TRACE("\n");
  if (!state)
  {
    WINE_ERR("NULL internal state (init not called?)\n");
    return NULL;
  }
  return state->getSteamClient();
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

