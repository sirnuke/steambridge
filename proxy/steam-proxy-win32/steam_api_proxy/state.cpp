// state.cpp - Records the state of the app, specifically stuff that's
//             internal and can't be cleanly tossed back to the app via 
//             the existing (and expected) classes/interfaces.

#include "stdafx.h"

#include "apps_api.h"
#include "friends_api.h"
#include "logging.h"
#include "state.h"
#include "user_api.h"
#include "userstats_api.h"

AppState state;


AppState::AppState() 
  : safeMode(false), steamUser(NULL), steamFriends(NULL), steamApps(NULL),
    steamUserStats(NULL)
{
  __LOG_MSG__("Constructing...");
}

AppState::~AppState()
{
  __LOG_MSG__("Destructing...");
  callbacks.clear();
  if (steamUser)
    delete steamUser;
  if (steamFriends)
    delete steamFriends;
  if (steamApps)
    delete steamApps;
  if (steamUserStats)
    delete steamUserStats;
}

void AppState::addCallback(class CCallbackBase *callback)
{
  callbacks.push_back(callback);
}

SteamUserWrapper *AppState::getSteamUser()
{ 
  if (!steamUser)
    steamUser = new SteamUserWrapper();
  return steamUser; 
}

SteamFriendsWrapper *AppState::getSteamFriends()
{
  if (!steamFriends)
    steamFriends = new SteamFriendsWrapper();
  return steamFriends;
}

SteamAppsWrapper *AppState::getSteamApps()
{
  if (!steamApps)
    steamApps = new SteamAppsWrapper();
  return steamApps;
}

SteamUserStatsWrapper *AppState::getSteamUserStats()
{
  if (!steamUserStats)
    steamUserStats = new SteamUserStatsWrapper();
  return steamUserStats;
}

void AppState::setAppId(int appid) { this->appid = appid; }
int  AppState::getAppId() { return appid; }
void AppState::setSafeMode(bool safe) { safeMode = safe; }
bool AppState::getSafeMode() { return safeMode; }


