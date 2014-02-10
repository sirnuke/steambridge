// state.cpp - Records the state of the app, specifically stuff that's
//             internal and can't be cleanly tossed back to the app via 
//             the existing (and expected) classes/interfaces.

#include "stdafx.h"

#include "apps_api.h"
#include "client_api.h"
#include "friends_api.h"
#include "logging.h"
#include "state.h"
#include "user_api.h"
#include "userstats_api.h"

AppState state;


AppState::AppState() 
  : safeMode(false), steamClient(NULL), steamUser(NULL), steamFriends(NULL),
    steamApps(NULL), steamUserStats(NULL)
{
  __TRACE("(this=0x%p)", this);
}

AppState::~AppState()
{
  __TRACE("(this=0x%p)", this);
  callbacks.clear();
  if (steamClient)    delete steamClient;
  if (steamUser)      delete steamUser;
  if (steamFriends)   delete steamFriends;
  if (steamApps)      delete steamApps;
  if (steamUserStats) delete steamUserStats;
}

void AppState::addCallback(class CCallbackBase *callback)
{
  __TRACE("(0x%p)", callback);
  callbacks.push_back(callback);
}

SteamClientWrapper *AppState::getSteamClient()
{
  __TRACE("()");
  if (!steamClient)
  {
    steamClient = new SteamClientWrapper();
    __LOG("Created ISteamClient wrapper (0x%p)", steamClient);
  }
  return steamClient;
}

SteamUserWrapper *AppState::getSteamUser()
{
  __TRACE("()");
  if (!steamUser)
  { 
    steamUser = new SteamUserWrapper();
    __LOG("Creating ISteamUser wrapper (0x%p)", steamUser);
  }
  return steamUser; 
}

SteamFriendsWrapper *AppState::getSteamFriends()
{
  __TRACE("()");
  if (!steamFriends)
  {
    steamFriends = new SteamFriendsWrapper();
    __LOG("Creating ISteamFriends wrapper (0x%p)", steamFriends);
  }
  return steamFriends;
}

SteamAppsWrapper *AppState::getSteamApps()
{
  __TRACE("()");
  if (!steamApps)
  {
    steamApps = new SteamAppsWrapper();
    __LOG("Creating ISteamApps wrapper (0x%p)", steamApps);
  }
  return steamApps;
}

SteamUserStatsWrapper *AppState::getSteamUserStats()
{
  __TRACE("()");
  if (!steamUserStats)
  {
    steamUserStats = new SteamUserStatsWrapper();
    __LOG("Creating ISteamUserStats wrapper (0x%p)", steamUserStats);
  }
  return steamUserStats;
}

void AppState::setAppId(int appid)
{
  __TRACE("(%i)", appid);
  this->appid = appid;
}

int  AppState::getAppId()
{
  __TRACE("()");
  return appid;
}

void AppState::setSafeMode(bool safe)
{
  __TRACE("(%i)", safe);
  safeMode = safe;
}

bool AppState::getSafeMode()
{
  __TRACE("()");
  return safeMode;
}


