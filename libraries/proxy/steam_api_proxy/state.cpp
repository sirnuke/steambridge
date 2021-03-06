// state.cpp - Records the state of the app, specifically stuff that's
//             internal and can't be cleanly tossed back to the app via 
//             the existing (and expected) classes/interfaces
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include "stdafx.h"

#include "apps_api.h"
#include "client_api.h"
#include "friends_api.h"
#include "logging.h"
#include "state.h"
#include "user_api.h"
#include "userstats_api.h"
#include "utils_api.h"

AppState state;


AppState::AppState() 
  : safeMode(false), steamClient(NULL), steamUser(NULL), steamFriends(NULL),
    steamApps(NULL), steamUserStats(NULL), steamUtils(NULL)
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
  if (steamUtils)     delete steamUtils;
}

void AppState::addCallback(class CCallbackBase *callback)
{
  __TRACE("(0x%p)", callback);
  callbacks.push_back(callback);
}

SteamClient *AppState::getSteamClient()
{
  __TRACE("()");
  if (!steamClient)
  {
    steamClient = new SteamClient();
    __LOG("Created ISteamClient wrapper (0x%p)", steamClient);
  }
  return steamClient;
}

SteamUser *AppState::getSteamUser()
{
  __TRACE("()");
  if (!steamUser)
  { 
    steamUser = new SteamUser();
    __LOG("Creating ISteamUser wrapper (0x%p)", steamUser);
  }
  return steamUser; 
}

SteamFriends *AppState::getSteamFriends()
{
  __TRACE("()");
  if (!steamFriends)
  {
    steamFriends = new SteamFriends();
    __LOG("Creating ISteamFriends wrapper (0x%p)", steamFriends);
  }
  return steamFriends;
}

SteamApps *AppState::getSteamApps()
{
  __TRACE("()");
  if (!steamApps)
  {
    steamApps = new SteamApps();
    __LOG("Creating ISteamApps wrapper (0x%p)", steamApps);
  }
  return steamApps;
}

SteamUserStats *AppState::getSteamUserStats()
{
  __TRACE("()");
  if (!steamUserStats)
  {
    steamUserStats = new SteamUserStats();
    __LOG("Creating ISteamUserStats wrapper (0x%p)", steamUserStats);
  }
  return steamUserStats;
}

SteamUtils *AppState::getSteamUtils()
{
  __TRACE("()");
  if (!steamUtils)
  {
    steamUtils = new SteamUtils();
    __LOG("Creating ISteamUtils wrapper (0x%p)", steamUtils);
  }
  return steamUtils;
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


