// meta.cpp - Implements various meta API calls.

#include <cstdio>

#include <string>

#define NOMINMAX
#include <windef.h>
#include <winbase.h>
#include <wine/debug.h>

#include <steam_api.h>

#include "api.h"
#include "logging.h"

#include "version.h"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

const char *steam_bridge_INFO 
  = "Visit http://github.com/sirnuke/steambridge for more information!";

extern "C"
{

STEAM_API_BRIDGE_API const char *steam_bridge_version_string()
{
  WINE_TRACE("\n");
  return steam_bridge_VERSION_STRING;
}

STEAM_API_BRIDGE_API const char *steam_bridge_info_string()
{
  WINE_TRACE("\n");
  return steam_bridge_INFO;
}

}

