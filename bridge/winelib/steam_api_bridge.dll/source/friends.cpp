// friends.cpp - Implements various functions related to the ISteamFriends class.

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


STEAM_API_BRIDGE_API class ISteamFriends *steam_bridge_SteamFriends()
{
  // TODO: Probably throw an assert here
  if (!context) return NULL;
  return context->getSteamFriends();
}

} // extern "C"

