// state.h - Records the state of the app, specifically stuff that's
//           internal and can't be cleanly tossed back to the app via 
//           the existing (and expected) classes/interfaces.
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#pragma once

#include <deque>

class SteamClientWrapper;
class SteamUser;
class SteamFriends;
class SteamApps;
class SteamUserStats;
class SteamUtils;

class AppState
{
  public:
    AppState();
    ~AppState();

    void setAppId(int appid);
    int getAppId();

    void setSafeMode(bool safe);
    bool getSafeMode();

    void addCallback(class CCallbackBase *callback);

    SteamClientWrapper *getSteamClient();
    SteamUser *getSteamUser();
    SteamFriends *getSteamFriends();
    SteamApps *getSteamApps();
    SteamUserStats *getSteamUserStats();
    SteamUtils *getSteamUtils();

  private:
    int appid;

    bool safeMode;

    std::deque<class CCallbackBase *> callbacks;

    SteamClientWrapper *steamClient;
    SteamUser *steamUser;
    SteamFriends *steamFriends;
    SteamApps *steamApps;
    SteamUserStats *steamUserStats;
    SteamUtils *steamUtils;
};

extern AppState state;

