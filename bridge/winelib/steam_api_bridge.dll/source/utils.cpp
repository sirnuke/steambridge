// utils.cpp - Implements various functions related to the ISteamUtils class.

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

STEAM_API_BRIDGE_API ISteamUtils *steam_bridge_SteamUtils()
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

