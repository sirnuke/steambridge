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

STEAM_API_BRIDGE_API const char *steam_bridge_SteamFriends_GetPersonaName(
    class ISteamFriends *steamFriends)
{
  WINE_TRACE("(0x%p)", steamFriends);

  if (!steamFriends)
    __ABORT("NULL steamFriends pointer!");

  return steamFriends->GetPersonaName();
}

STEAM_API_BRIDGE_API int steam_bridge_SteamFriends_GetFriendCount(
    class ISteamFriends *steamFriends, int iFriendFlags)
{
  WINE_TRACE("(0x%p)", steamFriends);

  if (!steamFriends)
    __ABORT("NULL steamFriends pointer!");

  return steamFriends->GetFriendCount(iFriendFlags);
}

STEAM_API_BRIDGE_API class ISteamFriends *steam_bridge_SteamFriends()
{
  WINE_TRACE("()");

  if (!context)
  {
    WINE_ERR("Context is NULL, Init either failed or wasn't called\n");
    return NULL;
  }

  return context->getSteamFriends();
}

} // extern "C"

