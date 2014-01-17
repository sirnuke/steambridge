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

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);


extern "C"
{

STEAM_API_BRIDGE_API class ISteamUser *steam_bridge_SteamUser(const char *version)
{
  // TODO: It might be easier/safer to just reimplement the
  //       CSteamAPIContext.  Calling this function multiple types probably
  //       create multiple copies of ISteamUser, while just one exists in 
  //       the real API.  Note that this is handled by the Proxy API at 
  //       the moment.
  ISteamUser *user = SteamClient()->GetISteamUser(SteamAPI_GetHSteamUser(), SteamAPI_GetHSteamUser(), version);
  return user;
}

}

