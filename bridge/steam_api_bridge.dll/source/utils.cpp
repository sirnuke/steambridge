// utils.cpp - Implements various functions related to the ISteamUtils class
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

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

extern "C"
{

void steam_bridge_SteamUtils_SetOverlayNotificationPosition(
    ISteamUtils *steamUtils, int eNotificationPosition)
{
  WINE_TRACE("(%i)\n", eNotificationPosition);
  if (!steamUtils) __ABORT("NULL steamUser pointer!");

  steamUtils->SetOverlayNotificationPosition(
      (ENotificationPosition)(eNotificationPosition));
}

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

