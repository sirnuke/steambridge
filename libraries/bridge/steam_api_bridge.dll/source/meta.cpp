// meta.cpp - Implements various meta API calls
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include <cstdio>

#include <string>

#define NOMINMAX
#include <wine/debug.h>

#include <steam_api.h>

#include "config.h"

#include "api.h"
#include "logging.h"


WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

const char *steambridge_INFO = "Visit " _STEAM_BRIDGE_WEBPAGE 
  " for more information on " _STEAM_BRIDGE_APPNAME "!";

extern "C"
{

STEAM_API_BRIDGE_API const char *steambridge_version_string()
{
  WINE_TRACE("\n");
  return _STEAM_BRIDGE_VERSION_LONG;
}

STEAM_API_BRIDGE_API const char *steambridge_info_string()
{
  WINE_TRACE("\n");
  return steambridge_INFO;
}

}

