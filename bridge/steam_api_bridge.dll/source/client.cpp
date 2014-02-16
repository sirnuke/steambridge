// client.cpp - Implements various functions related to the ISteamClient class
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include <steam_api.h>

#include <dlfcn.h>

#define NOMINMAX
#include <wine/debug.h>

#include "api.h"
#include "logging.h"
#include "state.h"

typedef ISteamClient *(*steam_api_SteamClient_t)(void);

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

extern "C"
{

static void steam_bridge_WarningHookCallback(int severity, const char *message)
{
  WINE_TRACE("(%i,\"%s\")\n", severity, message);
  if (!state) __ABORT("NULL internal state");
  SteamAPIWarningMessageHook_t func
    = (SteamAPIWarningMessageHook_t)(state->getWarningHookFunction());
  (*func)(severity, message);
}

STEAM_API_BRIDGE_API ISteamClient *SteamClient_()
{
  WINE_TRACE("\n");
  if (!state) __ABORT("NULL internal state (init not called?)");
  __DLSYM_GET(steam_api_SteamClient_t, api, "SteamClient");
  return (*api)();
}

STEAM_API_BRIDGE_API void SteamClient_SetWarningMessageHook(ISteamClient *steamClient,
    SteamAPIWarningMessageHook_t func)
{
  WINE_TRACE("(%p,%p)\n", steamClient, func);

  if (!state) __ABORT("NULL internal state");
  if (!steamClient) __ABORT("NULL steamClient!");
  if (!func) __ABORT("NULL callback func!");

  state->setWarningHookFunction(func);
  steamClient->SetWarningMessageHook(&steam_bridge_WarningHookCallback);
}

} // extern "C"

