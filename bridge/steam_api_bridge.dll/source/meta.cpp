// meta.cpp - Implements various meta API calls.

#include <cstdio>

#include <string>

#define NOMINMAX
#include <wine/debug.h>

#include <steam_api.h>

#include "config.h"

#include "api.h"
#include "logging.h"


WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

const char *steam_bridge_INFO = "Visit " _STEAM_BRIDGE_WEBPAGE 
  " for more information on " _STEAM_BRIDGE_APPNAME "!";

extern "C"
{

STEAM_API_BRIDGE_API const char *steam_bridge_version_string()
{
  WINE_TRACE("\n");
  return _STEAM_BRIDGE_VERSION_LONG;
}

STEAM_API_BRIDGE_API const char *steam_bridge_info_string()
{
  WINE_TRACE("\n");
  return steam_bridge_INFO;
}

}

