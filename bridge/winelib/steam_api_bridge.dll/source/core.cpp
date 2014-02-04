// core.cpp - Handles the core API calls

// C headers
#include <cstdio>

#include <deque>
#include <fstream>
#include <string>

// Boost headers (settings management)
// TODO: Bringing these inline with the project at large would be nice.
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

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

// TODO: Can this be safely hardcoded?
#define _SETTINGS_FILENAME "~/.steam/root/_steam_bridge_settings.config"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

SteamAPIContext::SteamAPIContext(int appid) 
  : steamUser(NULL), steamFriends(NULL), steamUtils(NULL),
    steamMatchmaking(NULL), steamUserStats(NULL), steamApps(NULL),
    steamMatchmakingServers(NULL), steamNetworking(NULL),
    steamRemoteStorage(NULL), steamScreenshots(NULL), steamHTTP(NULL),
    steamUnifiedMessages(NULL)
{
  // TODO: Lessss work in the constructor!

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
      __ABORT("Unknown application ID (%i)!", appid);
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

void SteamAPIContext::addCallback(CCallbackBase *wrapper,
    CCallbackBase *reference)
{
  WINE_TRACE("(0x%p,0x%p)\n", wrapper, reference);
  callbacks.push_back(wrapper);
  references[reference] = wrapper;
}

CCallbackBase *SteamAPIContext::getCallback(CCallbackBase *reference)
{
  return references[reference];
}

// NOTE: This function assumes wrapper has already been deregistered
// NOTE: This doesn't delete the wrapper becaussss Cplusplussss and
//       non-virtual destructors.
void SteamAPIContext::removeCallback(CCallbackBase *reference)
{
  WINE_TRACE("(0x%p)\n", reference);

  CCallbackBase *wrapper = references[reference];
  if (wrapper == NULL)
  {
    WINE_ERR("Unable to find corresponding wrapper for (0x%p)\n", reference);
    return;
  }
  std::deque<CCallbackBase *>::iterator it;
  for (it = callbacks.begin(); it != callbacks.end(); it++)
    if (*it == wrapper) break;
  if (it == callbacks.end())
  {
    WINE_ERR("Unable to find Callback Wrapper (0x%p) in the deque, "
        "reference is (0x%p)\n", wrapper, reference);
    return;
  }
  callbacks.erase(it);
}

SteamAPIContext *context = NULL;

static int steam_bridge_get_appid()
{
  int appid = 0;
  std::ifstream file;
  // TODO: we may want some sort of steam_appid_override.txt
  file.open("steam_appid.txt");
  if (file.fail())
    __ABORT("Unable to open 'steam_appid.txt'");
  // TODO: Error checkin' and all that yo.
  file >> appid;
  file.close();

  return appid;
}

extern "C"
{

// TODO: Would we want/need a wrapper for the straight Init() function?
//       Maybe one that creates a context that uses the default ISteam*
//       classes?
bool steam_bridge_SteamAPI_InitSafe()
{
  WINE_TRACE("\n");

  if (context == NULL)
  {
    int appid = steam_bridge_get_appid();
    if (!SteamAPI_InitSafe())
    {
      WINE_WARN("SteamAPI_InitSafe failed! (Look for Steam messages)\n");
      return false;
    }
    context = new SteamAPIContext(appid);
    if (!context)
      __ABORT("Unable to allocate SteamAPIContext (internal context state)!");
    WINE_TRACE("Created Internal API Context (0x%p)\n", context);
  }
  else
    WINE_WARN("Init called twice (perhaps internally the first time)\n");
  return true;
}

STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_Shutdown()
{
  WINE_TRACE("\n");
  if (context == NULL)
    WINE_WARN("Shutdown called when not initialized!\n");
  else
  {
    delete context;
    context = NULL;
    SteamAPI_Shutdown();
    WINE_TRACE("SteamAPI Shutdown\n");
  }
}

}
