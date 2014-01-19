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
#include "core.h"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

SteamAPIContext::SteamAPIContext(int appid) 
  : appid(appid), steamUser(NULL), steamFriends(NULL), steamUtils(NULL),
    steamMatchmaking(NULL), steamUserStats(NULL), steamApps(NULL),
    steamMatchmakingServers(NULL), steamNetworking(NULL),
    steamRemoteStorage(NULL), steamScreenshots(NULL), steamHTTP(NULL),
    steamUnifiedMessages(NULL)
{
  // TODO: Should do this check in some form
	// if (!SteamClient())

  // TODO: lol hardcoding.  Placeholders ahoy!
  // TODO: Might want to make this part of a seperate init function, like the headers.
  // TODO: The official API checks that each pointer doesn't return NULL.
  //       This is a Good Idea that should be used here.

	HSteamUser steamUserHandle = SteamAPI_GetHSteamUser();
	HSteamPipe steamPipeHandle = SteamAPI_GetHSteamPipe();

  steamUser = SteamClient()->GetISteamUser(steamUserHandle, steamPipeHandle,
      "SteamUser016");

  steamFriends = SteamClient()->GetISteamFriends(steamUserHandle,
      steamPipeHandle, "SteamFriends013");

  steamUtils = SteamClient()->GetISteamUtils(steamPipeHandle, "SteamUtils005");

  steamMatchmaking = SteamClient()->GetISteamMatchmaking(steamUserHandle,
      steamPipeHandle, "SteamMatchMaking009");

  steamMatchmakingServers = SteamClient()->GetISteamMatchmakingServers(
      steamUserHandle, steamPipeHandle, "SteamMatchMakingServers002");

  steamUserStats = SteamClient()->GetISteamUserStats(steamUserHandle,
      steamPipeHandle, "STEAMUSERSTATS_INTERFACE_VERSION011");

  steamApps = SteamClient()->GetISteamApps(steamUserHandle, steamPipeHandle,
      "STEAMAPPS_INTERFACE_VERSION005");

  steamNetworking = SteamClient()->GetISteamNetworking(steamUserHandle,
      steamPipeHandle, "SteamNetworking005");

  steamRemoteStorage = SteamClient()->GetISteamRemoteStorage(steamUserHandle,
      steamPipeHandle, "STEAMREMOTESTORAGE_INTERFACE_VERSION008");

  steamScreenshots = SteamClient()->GetISteamScreenshots(steamUserHandle,
      steamPipeHandle, "STEAMSCREENSHOTS_INTERFACE_VERSION001");

  steamHTTP = SteamClient()->GetISteamHTTP(steamUserHandle, steamPipeHandle,
      "STEAMHTTP_INTERFACE_VERSION001");

  // TODO: Not all apps will support all interfaces, in this case
  //       Audiosurf's demo doesn't have support for the UnifiedMessages
  //       class.
  steamUnifiedMessages = NULL;
  //SteamClient()->GetISteamUnifiedMessages(steamUserHandle, steamPipeHandle,
  //  "STEAMUNIFIEDMESSAGES_INTERFACE_VERSION001");
}

// TODO: This might need to be accessible by other parts of the bridge.
SteamAPIContext *context = NULL;


extern "C"
{

bool steam_bridge_SteamAPI_InitSafe(int appid)
{
  WINE_TRACE("(%i)", appid);
  if (context == NULL)
  {
    bool b = SteamAPI_InitSafe();
    if (!b) return b;
    context = new SteamAPIContext(appid);
    if (!context) return false;
  }
  // TODO: Warn if init'd twice?
  return true;
}

}
