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

STEAM_API_BRIDGE_API ISteamClient *steam_bridge_SteamClient()
{
  WINE_TRACE("\n");

  if (context == NULL)
    __ABORT("SteamClient called with a NULL context (init not called?)\n");

  __DLSYM_GET(steam_api_SteamClient_t, api, "SteamClient");
  return (*api)();
}

}

