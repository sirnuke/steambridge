// client.cpp - Implements various functions related to the ISteamClient class.

#include <steam_api.h>

#include <dlfcn.h>

#define NOMINMAX
#include <windef.h>
#include <winbase.h>
#include <wine/debug.h>

#include "api.h"
#include "core.h"
#include "logging.h"

typedef ISteamClient *(*steam_api_SteamClient_t)(void);

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);


extern "C"
{

static void steam_bridge_WarningHookCallback(int severity, const char *message)
{
  WINE_TRACE("(%i,\"%s\")\n", severity, message);
  if (!context) __ABORT("NULL context");
  SteamAPIWarningMessageHook_t func
    = (SteamAPIWarningMessageHook_t)(context->getWarningHookFunction());
  (*func)(severity, message);
}

STEAM_API_BRIDGE_API ISteamClient *steam_bridge_SteamClient()
{
  WINE_TRACE("\n");

  if (context == NULL)
    __ABORT("SteamClient called with a NULL context (init not called?)\n");

  __DLSYM_GET(steam_api_SteamClient_t, api, "SteamClient");
  return (*api)();
}

STEAM_API_BRIDGE_API void steam_bridge_SteamClient_SetWarningMessageHook(
    ISteamClient *steamClient, steam_bridge_WarningHookFunc func)
{
  WINE_TRACE("(%p,%p)\n", steamClient, func);

  if (!steamClient) __ABORT("NULL steamClient!");
  if (!func) __ABORT("NULL callback func!");
  if (!context) __ABORT("NULL context (init not called?)\n");
  context->setWarningHookFunction(func);
  steamClient->SetWarningMessageHook(&steam_bridge_WarningHookCallback);
}

}

