// state.h - Implements the internal State class
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

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
#include "picojson.h"

#include "config.h"

#define _APPDB_APIVERSIONS "apiversions"

typedef ISteamClient *(*steam_api_SteamClient_t)(void);
typedef HSteamUser (*steam_api_GetHSteamUser_t)(void);
typedef HSteamPipe (*steam_api_GetHSteamPipe_t)(void);

// TODO: We should track userids, and tie disclaimer to it.

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

static std::string _state_convert_path(const std::string &source)
{
  WINE_TRACE("(source=%s)\n", source.c_str());
  std::string result = source;
  if (!source.empty() && source.at(0) == '~')
  {
    std::string home;
    char *homeStr = NULL;

    if ((homeStr = getenv("HOME")) == NULL)
    {
      // Harumph
      struct passwd *pw = getpwuid(getuid());
      if (!pw) __ABORT("getpwuid failed (!): %s", strerror(errno));
      home = pw->pw_dir;
    }
    else
      home = homeStr;

    if (home.empty()) __ABORT("Unable to find a valid home directory!");

    result = home + result.substr(1);
  }
  WINE_TRACE("converted path is '%s'\n", result.c_str());
  return result;
}

State::State()
  : steamClient(NULL), steamUser(NULL), steamFriends(NULL),
    steamUtils(NULL), steamMatchmaking(NULL), steamUserStats(NULL),
    steamApps(NULL), steamMatchmakingServers(NULL), steamNetworking(NULL),
    steamRemoteStorage(NULL), steamScreenshots(NULL), steamHTTP(NULL),
    steamUnifiedMessages(NULL), initialized(false), steamAPIHandle(NULL),
    appid(0), disclaimer(false)
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
  std::string local = _state_convert_path(_STEAM_BRIDGE_LOCAL);

  if (stat(local.c_str(), &rootDir) != 0)
  {
    if (errno != ENOENT)
      __ABORT("Local directory \"%s\" doesn't exist!", _STEAM_BRIDGE_LOCAL);
    else
      __ABORT("Unable to stat local directory \"%s\": %s\n",
          _STEAM_BRIDGE_LOCAL, strerror(errno));
  }
  else if (S_ISDIR(rootDir.st_mode) == 0)
    __ABORT("Local directory \"%s\" exists, but isn't a directory!\n",
        _STEAM_BRIDGE_LOCAL);
}

void State::loadSteamAPI()
{
  WINE_TRACE("(this=%p)\n", this);

  std::string libPath = _state_convert_path(_STEAM_BRIDGE_API_LIB);

  // TODO: RTLD_LAZY?  Not that it likely makes a huge difference.
  steamAPIHandle = dlopen(libPath.c_str(), RTLD_NOW);
  
  // TODO: Can/should we check elsewhere?
  if (!steamAPIHandle)
    __ABORT("dlopen on \"%s\" failed: %s", libPath.c_str(), dlerror());
}

bool State::readConfiguration()
{
  WINE_TRACE("(this=%p\n", this);

  disclaimer = false;

  std::string filename = _state_convert_path(_STEAM_BRIDGE_CONFIG);

  std::ifstream in(filename.c_str());

  if (!in)
  {
    WINE_WARN("Unable to open %s\n", filename.c_str());
    return false;
  }

  picojson::value data;
  in >> data;

  if (!in)
  {
    WINE_ERR("Unable to read %s as JSON\n", filename.c_str());
    return false;
  }

  if (!data.is<picojson::value::object>())
  {
    WINE_ERR("Root element of %s isn't an object\n", filename.c_str());
    return false;
  }

  const picojson::value &disclaimer = data.get("disclaimer");

  if (disclaimer.is<bool>())
    this->disclaimer = disclaimer.get<bool>();
  else
    WINE_ERR("Unable to read disclaimer as a bool in %s\n", filename.c_str());

  return true;
}

bool State::saveConfiguration()
{
  WINE_TRACE("(this=%p)\n", this);

  std::string filename = _state_convert_path(_STEAM_BRIDGE_CONFIG);

  std::ofstream out(filename.c_str());

  out << "{ ";
  out << "\"disclaimer\" : ";
  if (disclaimer)
    out << "true\n";
  else
    out << "false\n";
  out << "}" << std::endl;

  WINE_TRACE("Saved the configuration\n");
  return true;
}

void State::loadSteamAPIVersions()
{
  WINE_TRACE("(%p)\n", this);

  __DLSYM_GET(steam_api_SteamClient_t, api_SteamClient, "SteamClient");
  steamClient = (*api_SteamClient)();
  if (!steamClient)
    __ABORT("SteamClient() returns NULL! (InitSafe not called?)");

  std::stringstream ss;
  ss << _state_convert_path(_STEAM_BRIDGE_APPDB_ROOT) << "/" << appid << "/"
     << _STEAM_BRIDGE_APPDB_CONFIG;
  std::string filename = ss.str();

  std::ifstream in(filename.c_str());

  if (!in) __ABORT("Unable to open '%s'", filename.c_str());

  picojson::value data;

  in >> data;

  if (!in)
    __ABORT("Error reading '%s': %s", filename.c_str(),
        picojson::get_last_error().c_str());

  if (!data.is<picojson::value::object>())
    __ABORT("Root element in '%s' isn't an object", filename.c_str());

  const picojson::value &api = data.get(_APPDB_APIVERSIONS);

  if (!api.is<picojson::object>())
    __ABORT(_APPDB_APIVERSIONS " element in '%s' isn't an object",
        filename.c_str());

  const picojson::value &user = api.get("user");
  if (user.is<std::string>()) userVersion = user.get<std::string>();

  const picojson::value &friends = api.get("friends");
  if (friends.is<std::string>()) friendsVersion = friends.get<std::string>();

  const picojson::value &utils = api.get("utils");
  if (utils.is<std::string>()) utilsVersion = utils.get<std::string>();

  const picojson::value &matchmaking = api.get("matchmaking");
  if (matchmaking.is<std::string>())
    matchmakingVersion = matchmaking.get<std::string>();

  const picojson::value &matchmakingServers = api.get("matchmaking_servers");
  if (matchmakingServers.is<std::string>())
    matchmakingServersVersion = matchmakingServers.get<std::string>();

  const picojson::value &userStats = api.get("user_stats");
  if (userStats.is<std::string>())
    userStatsVersion = userStats.get<std::string>();

  const picojson::value &apps = api.get("apps");
  if (apps.is<std::string>()) appsVersion = apps.get<std::string>();

  const picojson::value &networking = api.get("networking");
  if (networking.is<std::string>())
    networkingVersion = networking.get<std::string>();

  const picojson::value &remoteStorage = api.get("remote_storage");
  if (remoteStorage.is<std::string>())
    remoteStorageVersion = remoteStorage.get<std::string>();

  const picojson::value &screenshots = api.get("screenshots");
  if (screenshots.is<std::string>())
    screenshotsVersion = screenshots.get<std::string>();

  const picojson::value &http = api.get("http");
  if (http.is<std::string>()) httpVersion = http.get<std::string>();

  const picojson::value &unifiedMessages = api.get("unified_messages");
  if (unifiedMessages.is<std::string>())
    unifiedMessagesVersion = unifiedMessages.get<std::string>();

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

