// friends.cpp - Implements various functions related to the ISteamFriends class
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

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

extern "C"
{

STEAM_API_BRIDGE_API const char *steam_bridge_SteamFriends_GetPersonaName(
    ISteamFriends *steamFriends)
{
  WINE_TRACE("(%p)\n", steamFriends);

  if (!steamFriends) __ABORT("NULL steamFriends pointer!");

  return steamFriends->GetPersonaName();
}

STEAM_API_BRIDGE_API int steam_bridge_SteamFriends_GetFriendCount(
    ISteamFriends *steamFriends, int iFriendFlags)
{
  WINE_TRACE("(%p,%i)\n", steamFriends, iFriendFlags);

  if (!steamFriends) __ABORT("NULL steamFriends pointer!");

  return steamFriends->GetFriendCount(iFriendFlags);
}

STEAM_API_BRIDGE_API void steam_bridge_SteamFriends_SetPlayedWith(
    ISteamFriends *steamFriends, CSteamID steamIDUserPlayedWith)
{
  WINE_TRACE("(%p,%llu)\n", steamFriends,
      steamIDUserPlayedWith.ConvertToUint64());

  if (!steamFriends) __ABORT("NULL steamFriends pointer!");

  steamFriends->SetPlayedWith(steamIDUserPlayedWith);
}

STEAM_API_BRIDGE_API class ISteamFriends *steam_bridge_SteamFriends()
{
  WINE_TRACE("\n");

  if (!state)
  {
    WINE_ERR("NULL internal state (init not called?)\n");
    return NULL;
  }

  return state->getSteamFriends();
}

} // extern "C"

