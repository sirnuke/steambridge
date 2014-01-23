// core.cpp - Handles the core API calls

// C headers
#include <cstdio>

#include <deque>
#include <string>

// Steam headers
#include <steam_api.h>

// Wine/Win32 headers
#define NOMINMAX
// TODO: We probably don't need either of these headers
#include <windef.h>
#include <winbase.h>
#include <wine/debug.h>

// Local headers
#include "api.h"
#include "core.h"
#include "logging.h"

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

  // TODO: Better way of caching versions
  std::string steamUserVersion, steamFriendsVersion, steamUtilsVersion,
    steamMatchmakingVersion, steamMatchmakingServersVersion,
    steamUserStatsVersion, steamAppsVersion, steamNetworkingVersion,
    steamRemoteStorageVersion, steamScreenshotsVersion, steamHTTPVersion,
    steamUnifiedMessagesVersion;

  switch (appid)
  {
    case 12900: // Audiosurf
      steamUserVersion = "SteamUser016";
      steamFriendsVersion = "SteamFriends013";
      steamUtilsVersion = "SteamUtils005";
      steamMatchmakingVersion = "SteamMatchMaking009";
      steamMatchmakingServersVersion = "SteamMatchMakingServers002";
      steamUserStatsVersion = "STEAMUSERSTATS_INTERFACE_VERSION011";
      steamAppsVersion = "STEAMAPPS_INTERFACE_VERSION005";
      steamNetworkingVersion = "SteamNetworking005";
      steamRemoteStorageVersion = "STEAMREMOTESTORAGE_INTERFACE_VERSION008";
      steamScreenshotsVersion = "STEAMSCREENSHOTS_INTERFACE_VERSION001";
      steamHTTPVersion = "STEAMHTTP_INTERFACE_VERSION001";
      break;
    case 38730: // RUSH demo
      steamUserVersion = "SteamUser014";
      steamFriendsVersion = "SteamFriends007";
      steamUtilsVersion = "SteamUtils005";
      steamMatchmakingVersion = "SteamMatchMaking008";
      steamMatchmakingServersVersion = "SteamMatchMakingServers002";
      steamUserStatsVersion = "STEAMUSERSTATS_INTERFACE_VERSION007";
      steamAppsVersion = "STEAMAPPS_INTERFACE_VERSION003";
      steamNetworkingVersion = "SteamNetworking004";
      steamRemoteStorageVersion = "STEAMREMOTESTORAGE_INTERFACE_VERSION002";
    case 1522: // Defcon demo
      steamUserVersion = "SteamUser013";
      steamFriendsVersion = "SteamFriends005";
      steamUtilsVersion = "SteamUtils005";
      steamMatchmakingVersion = "SteamMatchMaking008";
      steamMatchmakingServersVersion = "SteamMatchMakingServers002";
      steamUserStatsVersion = "STEAMUSERSTATS_INTERFACE_VERSION007";
      steamAppsVersion = "STEAMAPPS_INTERFACE_VERSION003";
      steamNetworkingVersion = "SteamNetworking003";
      steamRemoteStorageVersion = "STEAMREMOTESTORAGE_INTERFACE_VERSION002";
      break;
    default:
      __ABORT_ARGS__("Unknown application ID!", "(%i)", appid);
      break;
  }

  HSteamUser steamUserHandle = SteamAPI_GetHSteamUser();
  HSteamPipe steamPipeHandle = SteamAPI_GetHSteamPipe();

  if (steamUserVersion == "")
    steamUser = NULL;
  else
    steamUser = SteamClient()->GetISteamUser(steamUserHandle, steamPipeHandle,
        steamUserVersion.c_str());

  if (steamFriendsVersion == "")
    steamFriends = NULL;
  else
    steamFriends = SteamClient()->GetISteamFriends(steamUserHandle,
        steamPipeHandle, steamFriendsVersion.c_str());

  if (steamUtilsVersion == "")
    steamUtils = NULL;
  else
    steamUtils = SteamClient()->GetISteamUtils(steamPipeHandle,
        steamUtilsVersion.c_str());

  if (steamMatchmakingVersion == "")
    steamMatchmaking = NULL;
  else
    steamMatchmaking = SteamClient()->GetISteamMatchmaking(steamUserHandle,
        steamPipeHandle, steamMatchmakingVersion.c_str());

  if (steamMatchmakingServersVersion == "")
    steamMatchmakingServers = NULL;
  else
    steamMatchmakingServers = SteamClient()->GetISteamMatchmakingServers(
        steamUserHandle, steamPipeHandle,
        steamMatchmakingServersVersion.c_str());

  if (steamUserStatsVersion == "")
    steamUserStats = NULL;
  else
    steamUserStats = SteamClient()->GetISteamUserStats(steamUserHandle,
        steamPipeHandle, steamUserStatsVersion.c_str());

  if (steamAppsVersion == "")
    steamApps = NULL;
  else
    steamApps = SteamClient()->GetISteamApps(steamUserHandle, steamPipeHandle,
        steamAppsVersion.c_str());

  if (steamNetworkingVersion == "")
    steamNetworking = NULL;
  else
    steamNetworking = SteamClient()->GetISteamNetworking(steamUserHandle,
        steamPipeHandle, steamNetworkingVersion.c_str());

  if (steamRemoteStorageVersion == "")
    steamRemoteStorage = NULL;
  else
    steamRemoteStorage = SteamClient()->GetISteamRemoteStorage(steamUserHandle,
        steamPipeHandle, steamRemoteStorageVersion.c_str());

  if (steamScreenshotsVersion == "")
    steamScreenshots = NULL;
  else
    steamScreenshots = SteamClient()->GetISteamScreenshots(steamUserHandle,
        steamPipeHandle, steamScreenshotsVersion.c_str());

  if (steamHTTPVersion == "")
    steamHTTP = NULL;
  else
    steamHTTP = SteamClient()->GetISteamHTTP(steamUserHandle, steamPipeHandle,
      steamHTTPVersion.c_str());

  if (steamUnifiedMessagesVersion == "")
    steamUnifiedMessages = NULL;
  else
    SteamClient()->GetISteamUnifiedMessages(steamUserHandle, steamPipeHandle,
        steamUnifiedMessagesVersion.c_str());
}

SteamAPIContext::~SteamAPIContext()
{
  // TODO: Delete all callbacks?
}

void SteamAPIContext::addCallback(class CCallbackBase *callback)
{
  callbacks.push_back(callback);
}

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
