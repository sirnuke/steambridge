// core.cpp - Handles the core API calls

// C headers
#include <cstdio>
#include <cstring>

// C++ headers
#include <deque>
#include <fstream>

// POSIX headers
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

// libconfig headers
#include <libconfig.h>

// Steam headers
#include <steam_api.h>

// Wine/Win32 headers
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wine/debug.h>

// Local headers
#include "api.h"
#include "core.h"
#include "logging.h"

#define _BRIDGE_DIR "/.steam/root/_steam_bridge/"
#define _APP_VERSION_DB "appids.cfg"
#define _CONFIGURATION_FILE "config.cfg"

// TODO: Polish and call ABORT where meaningful.  Internal errors not
//       related to SteamAPI should almost certainly be ABORT, not just
//       return false.
// TODO: We should track userids, and tie disclaimer to it.

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

SteamAPIContext::SteamAPIContext()
  : steamUser(NULL), steamFriends(NULL), steamUtils(NULL),
    steamMatchmaking(NULL), steamUserStats(NULL), steamApps(NULL),
    steamMatchmakingServers(NULL), steamNetworking(NULL),
    steamRemoteStorage(NULL), steamScreenshots(NULL), steamHTTP(NULL),
    steamUnifiedMessages(NULL), appid(0), disclaimer(false)
{
  WINE_TRACE("(this=0x%p)\n", this);
}

bool SteamAPIContext::prep(int appid)
{
  WINE_TRACE("(this=0x%p,%i)\n", this, appid);

  bool configChanged = false;

  if (appid == 0)
  {
    WINE_ERR("Received invalid appid of (%i)!\n", appid);
    return false;
  }
  if (this->appid != 0)
  {
    WINE_ERR("prep(%i) called twice!\n", appid);
    return false;
  }
  this->appid = appid;

  if (!SteamClient())
  {
    WINE_ERR("SteamClient() returns NULL! (InitSafe not called?)");
    return false;
  }

  if (!checkBridgeDirectory())
  {
    WINE_ERR("checkBridgeDirectory failed!\n");
    return false;
  }

  if (!readConfiguration())
  {
    WINE_ERR("readConfiguration failed!\n");
    return false;
  }

  if (!disclaimer)
  {
    int res = MessageBoxA(NULL, 
        "I would describe Valve as a diety of an Abrahamic religion. "
        "All powerful; all knowning, and yet unknowable. "
        "It might bestow free games. It might smite you for not properly "
        "sacrificing your goats."
        "\n\n"
        "SteamBridge doesn't hide itself, and arguably breaks the letter, "
        "though not the spirit, of the Steam Subscriber Agreement."
        "\n\n"
        "Do not continue with an important account.",
        "But First, a Word of Warning...",
        MB_ICONWARNING | MB_OKCANCEL);
    if (res == IDCANCEL)
    {
      WINE_TRACE("Disclaimer set to false and User said NO.\n");
      exit(0);
    }
    else if (res == IDOK)
    {
      WINE_TRACE("Disclaimer set to false, User said YES.\n");
      disclaimer = true;
      configChanged = true;
    }
    else
      __ABORT("Unknown MessageBoxA return value (%i) (?)", res);
  }

  if (configChanged)
  {
    if (!saveConfiguration())
    {
      WINE_ERR("saveConfiguration failed!\n");
      return false;
    }
  }

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
  case 1520: // Defcon real (probably the same?)
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
    WINE_ERR("Unknown application ID of (%i)!\n", appid);
    return false;
  }

  // TODO: Do we need to check this for error values?
  HSteamUser steamUserHandle = SteamAPI_GetHSteamUser();
  HSteamPipe steamPipeHandle = SteamAPI_GetHSteamPipe();

  if (!steamUserVersion.empty())
    steamUser = SteamClient()->GetISteamUser(steamUserHandle, steamPipeHandle,
        steamUserVersion.c_str());

  if (!steamFriendsVersion.empty())
    steamFriends = SteamClient()->GetISteamFriends(steamUserHandle,
        steamPipeHandle, steamFriendsVersion.c_str());

  if (!steamUtilsVersion.empty())
    steamUtils = SteamClient()->GetISteamUtils(steamPipeHandle,
        steamUtilsVersion.c_str());

  if (!steamMatchmakingVersion.empty())
    steamMatchmaking = SteamClient()->GetISteamMatchmaking(steamUserHandle,
        steamPipeHandle, steamMatchmakingVersion.c_str());

  if (!steamMatchmakingServersVersion.empty())
    steamMatchmakingServers = SteamClient()->GetISteamMatchmakingServers(
        steamUserHandle, steamPipeHandle,
        steamMatchmakingServersVersion.c_str());

  if (!steamUserStatsVersion.empty())
    steamUserStats = SteamClient()->GetISteamUserStats(steamUserHandle,
        steamPipeHandle, steamUserStatsVersion.c_str());

  if (!steamAppsVersion.empty())
    steamApps = SteamClient()->GetISteamApps(steamUserHandle, steamPipeHandle,
        steamAppsVersion.c_str());

  if (!steamNetworkingVersion.empty())
    steamNetworking = SteamClient()->GetISteamNetworking(steamUserHandle,
        steamPipeHandle, steamNetworkingVersion.c_str());

  if (!steamRemoteStorageVersion.empty())
    steamRemoteStorage = SteamClient()->GetISteamRemoteStorage(steamUserHandle,
        steamPipeHandle, steamRemoteStorageVersion.c_str());

  if (!steamScreenshotsVersion.empty())
    steamScreenshots = SteamClient()->GetISteamScreenshots(steamUserHandle,
        steamPipeHandle, steamScreenshotsVersion.c_str());

  if (!steamHTTPVersion.empty())
    steamHTTP = SteamClient()->GetISteamHTTP(steamUserHandle, steamPipeHandle,
      steamHTTPVersion.c_str());

  if (!steamUnifiedMessagesVersion.empty())
    steamUnifiedMessages = SteamClient()->GetISteamUnifiedMessages(
        steamUserHandle, steamPipeHandle, steamUnifiedMessagesVersion.c_str());

  // TODO: Check if any returned NULL?
  // TODO: Try to get ISteamController anyway?
  return true;
}

SteamAPIContext::~SteamAPIContext()
{
  // TODO: Delete all callbacks?
}

bool SteamAPIContext::checkBridgeDirectory()
{
  WINE_TRACE("(this=0x%p)\n", this);
  struct stat rootDir;
  std::string dir;
  char *home = NULL;

  if ((home = getenv("HOME")) == NULL)
  {
    // Harumph
    struct passwd *pw = getpwuid(getuid());
    if (!pw) __ABORT("getpwuid failed (!): %s", strerror(errno));
    dir = pw->pw_dir;
  }
  else
    dir = home;

  if (dir.empty()) __ABORT("Unable to find a valid home directory!");

  steamBridgeDir = dir + _BRIDGE_DIR;

  if (stat(steamBridgeDir.c_str(), &rootDir) != 0)
  {
    if (errno != ENOENT)
    {
      WINE_ERR("Unable to stat root directory \"%s\": %s\n",
          steamBridgeDir.c_str(), strerror(errno));
      return false;
    }
    if (mkdir(steamBridgeDir.c_str(),
          S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != 0)
    {
      WINE_ERR("Unable to create directory: %s\n", strerror(errno));
      return false;
    }
  }
  else if (S_ISDIR(rootDir.st_mode) == 0)
  {
    WINE_ERR("Root directory \"%s\" exists, but isn't a directory!\n", 
        steamBridgeDir.c_str());
    return false;
  }
  return true;
}

// Yuck yuck yuck?  Yuck yuck yuck.
#define _LIBCONFIG_WARN(MSG, ...) WINE_WARN(MSG ": %s@%i: %s\n", \
    ##__VA_ARGS__, config_error_file(&config), config_error_line(&config), \
      config_error_text(&config)); \

#define _LIBCONFIG_ERR(MSG, ...) WINE_ERR(MSG ": %s@%i: %s\n", \
    ##__VA_ARGS__, config_error_file(&config), config_error_line(&config), \
      config_error_text(&config)); \

#define _LIBCONFIG_ABORT(MSG, ...) __ABORT(MSG ": %s@%i: %s\n", \
    ##__VA_ARGS__, config_error_file(&config), config_error_line(&config), \
      config_error_text(&config)); \

bool SteamAPIContext::readConfiguration()
{
  WINE_TRACE("(this=0x%p\n", this);

  disclaimer = false;

  config_t config;
  config_init(&config);

  int disclaim = 0;

  std::string filename = steamBridgeDir + _CONFIGURATION_FILE;

  if (config_read_file(&config, filename.c_str()) != CONFIG_TRUE)
  {
    _LIBCONFIG_ERR("Unable to read configuration");
    config_destroy(&config);
    return true;
  }

  if (config_lookup_bool(&config, "steam_bridge.disclaimer", &disclaim) 
      != CONFIG_TRUE)
    _LIBCONFIG_WARN("Unable to read 'disclaimer' as a boolean setting");

  // TODO: Is it safe to assume libconfig's bool means true==1?
  if (disclaim == 1)
    disclaimer = true;
  else
  {
    if (disclaim != 0)
      WINE_ERR("Unknown (!?) 'bool' (%i) returned by libconfig for "
          "steam_bridge.disclaimer, defaulting to false\n", disclaim);
    disclaimer = false;
  }

  WINE_TRACE("Got disclaimer value of (%i)\n", disclaimer);

  config_destroy(&config);
  return true;
}

bool SteamAPIContext::saveConfiguration()
{
  WINE_TRACE("(this=0x%p)\n", this);

  std::string filename = steamBridgeDir + _CONFIGURATION_FILE;

  config_t config;
  config_init(&config);

  config_setting_t *root, *steam_bridge, *disclaimer;

  // These calls shouldn't fail for basically any reason - signifies an
  // internal logic error of some sort.
  root = config_root_setting(&config);
  if (!root) __ABORT("Unable to get the root element from libconfig!");

  steam_bridge = config_setting_add(root, "steam_bridge", CONFIG_TYPE_GROUP);
  if (!steam_bridge)
    __ABORT("Unable to add steam_bridge group to the root in libconfig!");

  disclaimer = config_setting_add(steam_bridge, "disclaimer", CONFIG_TYPE_BOOL);
  if (!disclaimer)
    __ABORT("Unable to add disclaimer to steam_bridge group in libconfig!");

  if (config_setting_set_bool(disclaimer, this->disclaimer) != CONFIG_TRUE)
    _LIBCONFIG_ABORT("Unable to set disclaimer");

  // This one, can, in fact, fail
  if (config_write_file(&config, filename.c_str()) != CONFIG_TRUE)
  {
    _LIBCONFIG_ERR("Unable to write configuration file");
    config_destroy(&config);
    return false;
  }

  config_destroy(&config);
  WINE_TRACE("Saved the configuration\n");
  return true;
}

#undef _LIBCONFIG_WARN
#undef _LIBCONFIG_ERR
#undef _LIBCONFIG_ABORT

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
  WINE_TRACE("\n");
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
    context = new SteamAPIContext();
    if (!context)
      __ABORT("Unable to allocate SteamAPIContext (internal context state)!");
    if (!context->prep(appid))
      __ABORT("Unable to setup the SteamAPIContext");
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
