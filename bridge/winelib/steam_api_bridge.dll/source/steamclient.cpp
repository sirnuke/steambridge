// steamclient.cpp - Wraps around various ISteamClient code.

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
#include "core.h"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);


extern "C"
{

STEAM_API_BRIDGE_API class ISteamUser *steam_bridge_SteamUser()
{
  // TODO: Should we print out a message in this case?  This should only
  //       happen if SteamAPI_Init isn't called, or if it fails.
  if (!context) return NULL;
  return context->getSteamUser();
}

}

