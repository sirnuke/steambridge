// state.h - Implements the internal State class.

// C headers
#include <cstdio>
#include <cstring>

// C++ headers
#include <deque>
#include <sstream>
#include <fstream>

// POSIX headers
#include <dlfcn.h>
#include <errno.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
#include "logging.h"
#include "state.h"

#define _STEAM_BRIDGE_ROOT_DIR "/.steam/root/SteamBridge/"
#define _APP_VERSION_DB "appdb/appid_db.cfg"
#define _CONFIGURATION_FILE "config.cfg"
#define _STEAM_API_SO "libsteam_api.so"

typedef ISteamClient *(*steam_api_SteamClient_t)(void);
typedef HSteamUser (*steam_api_GetHSteamUser_t)(void);
typedef HSteamPipe (*steam_api_GetHSteamPipe_t)(void);

// TODO: We should track userids, and tie disclaimer to it.

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

State::State()
  : steamUser(NULL), steamFriends(NULL), steamUtils(NULL),
    steamMatchmaking(NULL), steamUserStats(NULL), steamApps(NULL),
    steamMatchmakingServers(NULL), steamNetworking(NULL),
    steamRemoteStorage(NULL), steamScreenshots(NULL), steamHTTP(NULL),
    steamUnifiedMessages(NULL), initialized(false), steamAPIHandle(NULL),
    appid(0), disclaimer(false), warningHookFunction(NULL)
{
  WINE_TRACE("(this=%p)\n", this);
  getAppId();
  checkBridgeDirectory();
  loadSteamAPI();
}

void State::initialize()
{
  WINE_TRACE("(this=%p)\n", this);

  if (initialized) __ABORT("Function called twice!");

  bool configChanged = false;

  readConfiguration();

  if (!disclaimer)
  {
    // TODO: Move the message somewhere more readable?
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
    // This doesn't constitute an error by itself
    if (!saveConfiguration())
      WINE_ERR("saveConfiguration failed!\n");
  }

  loadSteamAPIVersions();

  initialized = true;
}

State::~State()
{
  // TODO: Delete all callbacks?

  if (steamAPIHandle)
  {
    int res = dlclose(steamAPIHandle);
    if (res != 0) WINE_ERR("dlclose failed (%i): %s\n", res, dlerror());
  }
}

void State::getAppId()
{
  WINE_TRACE("\n");

  appid = 0;
  std::ifstream file;
  // TODO: we may want some sort of steam_appid_override.txt
  file.open("steam_appid.txt");
  if (file.fail()) __ABORT("Unable to open steam_appid.txt");
  if (!(file >> appid))
    __ABORT("Unable to read contents of steam_appid.txt as an AppId_t (int)");
  file.close();
  if (appid == 0) __ABORT("Invalid appid of 0 read from steam_appid.txt");
}

// TODO: Should handle custom directories via enivornmental variables
void State::checkBridgeDirectory()
{
  WINE_TRACE("(this=%p)\n", this);
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

  steamBridgeRoot = dir + _STEAM_BRIDGE_ROOT_DIR;

  if (stat(steamBridgeRoot.c_str(), &rootDir) != 0)
  {
    if (errno != ENOENT)
      __ABORT("Root directory \"%s\" doesn't exist!", steamBridgeRoot.c_str());
    else
      __ABORT("Unable to stat root directory \"%s\": %s\n",
          steamBridgeRoot.c_str(), strerror(errno));
  }
  else if (S_ISDIR(rootDir.st_mode) == 0)
    __ABORT("Root directory \"%s\" exists, but isn't a directory!\n",
        steamBridgeRoot.c_str());
}

void State::loadSteamAPI()
{
  WINE_TRACE("(this=%p)\n", this);

  std::string libPath = steamBridgeRoot + _STEAM_API_SO;

  // TODO: RTLD_LAZY?  Not that it likely makes a huge difference.
  steamAPIHandle = dlopen(libPath.c_str(), RTLD_NOW);
  
  // TODO: Can/should we check elsewhere?
  if (!steamAPIHandle)
    __ABORT("dlopen on \"%s\" failed: %s", libPath.c_str(), dlerror());
}

// Yuck yuck yuck?  Yuck yuck yuck.
#define _LIBCONFIG_WARN(MSG, ...) WINE_WARN(MSG ": %s@%i: %s\n", \
    ##__VA_ARGS__, config_error_file(&config), config_error_line(&config), \
      config_error_text(&config));

#define _LIBCONFIG_ERR(MSG, ...) WINE_ERR(MSG ": %s@%i: %s\n", \
    ##__VA_ARGS__, config_error_file(&config), config_error_line(&config), \
      config_error_text(&config));

#define _LIBCONFIG_ABORT(MSG, ...) __ABORT(MSG ": %s@%i: %s\n", \
    ##__VA_ARGS__, config_error_file(&config), config_error_line(&config), \
      config_error_text(&config));

void State::readConfiguration()
{
  WINE_TRACE("(this=%p\n", this);

  disclaimer = false;

  config_t config;
  config_init(&config);

  int disclaim = 0;

  std::string filename = steamBridgeRoot + _CONFIGURATION_FILE;

  if (config_read_file(&config, filename.c_str()) != CONFIG_TRUE)
  {
    _LIBCONFIG_ERR("Unable to read configuration");
    config_destroy(&config);
    return;
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
}

bool State::saveConfiguration()
{
  WINE_TRACE("(this=%p)\n", this);

  std::string filename = steamBridgeRoot + _CONFIGURATION_FILE;

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

void State::loadSteamAPIVersions()
{
  WINE_TRACE("(%p)\n", this);

  config_setting_t *versions;
  config_t config;
  config_init(&config);

  __DLSYM_GET(steam_api_SteamClient_t, api_SteamClient, "SteamClient");
  ISteamClient *steamClient = (*api_SteamClient)();
  if (!steamClient)
    __ABORT("SteamClient() returns NULL! (InitSafe not called?)");

  char *string;

  std::string filename = steamBridgeRoot + _APP_VERSION_DB;

  if (config_read_file(&config, filename.c_str()) != CONFIG_TRUE)
  {
    _LIBCONFIG_ERR("Unable to read the appid db");
    config_destroy(&config);
    return;
  }

  std::stringstream ss;
  ss << "ids.id" << appid;

  if (config_lookup_string(&config, ss.str().c_str(), (const char **)(&string))
      != CONFIG_TRUE)
    _LIBCONFIG_ABORT("Unable to find appid (%u)", appid);

  appName = string;

  ss.clear();
  ss.str("");
  ss << "versions." << appName;

  versions = config_lookup(&config, ss.str().c_str());

  if (!versions)
    _LIBCONFIG_ABORT("Unable to find the API versions for %s (%u)",
        appName.c_str(), appid);

  if (config_setting_lookup_string(versions, "user", (const char **)(&string))
        == CONFIG_TRUE)
    userVersion = string;

  if (config_setting_lookup_string(versions, "friends",
        (const char **)(&string)) == CONFIG_TRUE)
    friendsVersion = string;

  if (config_setting_lookup_string(versions, "utils", (const char **)(&string))
        == CONFIG_TRUE)
    utilsVersion = string;

  if (config_setting_lookup_string(versions, "matchmaking",
        (const char **)(&string)) == CONFIG_TRUE)
    matchmakingVersion = string;

  if (config_setting_lookup_string(versions, "matchmaking_servers",
        (const char **)(&string)) == CONFIG_TRUE)
    matchmakingServersVersion = string;

  if (config_setting_lookup_string(versions, "user_stats",
        (const char **)(&string)) == CONFIG_TRUE)
    userStatsVersion = string;

  if (config_setting_lookup_string(versions, "apps", (const char **)(&string))
      == CONFIG_TRUE)
    appsVersion = string;

  if (config_setting_lookup_string(versions, "networking",
        (const char **)(&string)) == CONFIG_TRUE)
    networkingVersion = string;

  if (config_setting_lookup_string(versions, "remote_storage",
        (const char **)(&string)) == CONFIG_TRUE)
    remoteStorageVersion = string;

  if (config_setting_lookup_string(versions, "screenshots",
        (const char **)(&string)) == CONFIG_TRUE)
    screenshotsVersion = string;

  if (config_setting_lookup_string(versions, "http", (const char **)(&string))
        == CONFIG_TRUE)
    httpVersion = string;

  if (config_setting_lookup_string(versions, "unified_messages",
        (const char **)(&string)) == CONFIG_TRUE)
    unifiedMessagesVersion = string;

  __DLSYM_GET(steam_api_GetHSteamUser_t, api_GetHSteamUser,
      "SteamAPI_GetHSteamUser");
  __DLSYM_GET(steam_api_GetHSteamPipe_t, api_GetHSteamPipe,
      "SteamAPI_GetHSteamPipe");
  // TODO: Do we need to check this for error values?
  HSteamUser steamUserHandle = (*api_GetHSteamUser)();
  HSteamPipe steamPipeHandle = (*api_GetHSteamPipe)();

  if (!userVersion.empty())
    steamUser = steamClient->GetISteamUser(steamUserHandle,
      steamPipeHandle, userVersion.c_str());

  if (!friendsVersion.empty())
    steamFriends = steamClient->GetISteamFriends(steamUserHandle,
        steamPipeHandle, friendsVersion.c_str());

  if (!utilsVersion.empty())
    steamUtils = steamClient->GetISteamUtils(steamPipeHandle,
        utilsVersion.c_str());

  if (!matchmakingVersion.empty())
    steamMatchmaking = steamClient->GetISteamMatchmaking(steamUserHandle,
        steamPipeHandle, matchmakingVersion.c_str());

  if (!matchmakingServersVersion.empty())
    steamMatchmakingServers = steamClient->GetISteamMatchmakingServers(
        steamUserHandle, steamPipeHandle, matchmakingServersVersion.c_str());

  if (!userStatsVersion.empty())
    steamUserStats = steamClient->GetISteamUserStats(steamUserHandle,
        steamPipeHandle, userStatsVersion.c_str());

  if (!appsVersion.empty())
    steamApps = steamClient->GetISteamApps(steamUserHandle, steamPipeHandle,
        appsVersion.c_str());

  if (!networkingVersion.empty())
    steamNetworking = steamClient->GetISteamNetworking(steamUserHandle,
        steamPipeHandle, networkingVersion.c_str());

  if (!remoteStorageVersion.empty())
    steamRemoteStorage = steamClient->GetISteamRemoteStorage(steamUserHandle,
        steamPipeHandle, remoteStorageVersion.c_str());

  if (!screenshotsVersion.empty())
    steamScreenshots = steamClient->GetISteamScreenshots(steamUserHandle,
        steamPipeHandle, screenshotsVersion.c_str());

  if (!httpVersion.empty())
    steamHTTP = steamClient->GetISteamHTTP(steamUserHandle, steamPipeHandle,
      httpVersion.c_str());

  if (!unifiedMessagesVersion.empty())
    steamUnifiedMessages = steamClient->GetISteamUnifiedMessages(
        steamUserHandle, steamPipeHandle, unifiedMessagesVersion.c_str());

  // TODO: Check if any returned NULL?
  // TODO: Try to get ISteamController anyway?
  config_destroy(&config);
}

#undef _LIBCONFIG_WARN
#undef _LIBCONFIG_ERR
#undef _LIBCONFIG_ABORT

void State::addCallback(CCallbackBase *wrapper,
    CCallbackBase *reference)
{
  WINE_TRACE("(%p,%p)\n", wrapper, reference);
  callbacks.push_back(wrapper);
  references[reference] = wrapper;
}

CCallbackBase *State::getCallback(CCallbackBase *reference)
{
  return references[reference];
}

// NOTE: This function assumes wrapper has already been deregistered
// NOTE: This doesn't delete the wrapper becaussss Cplusplussss and
//       non-virtual destructors.
void State::removeCallback(CCallbackBase *reference)
{
  WINE_TRACE("(%p)\n", reference);

  CCallbackBase *wrapper = references[reference];
  if (wrapper == NULL)
    __ABORT("Unable to find corresponding wrapper for (%p)\n", reference);
  std::deque<CCallbackBase *>::iterator it;
  for (it = callbacks.begin(); it != callbacks.end(); it++)
    if (*it == wrapper) break;
  if (it == callbacks.end())
    __ABORT("Unable to find Callback Wrapper (%p) in the deque, "
        "reference is (%p)\n", wrapper, reference);
  callbacks.erase(it);
}

State *state = NULL;

