// core.cpp - Handles the core API calls

// C headers
#include <cstdio>

// Steam headers
#include <steam_api.h>

// Wine/Win32 headers
#include <windef.h>
#include <winbase.h>
#include <wine/debug.h>

// Local headers
#include "api.h"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

extern "C"
{

bool steam_bridge_SteamAPI_InitSafe()
{
  WINE_TRACE("");
  return SteamAPI_InitSafe();
}

}
