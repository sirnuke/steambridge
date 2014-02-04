// core.h - Headers for the core API calls.

#ifndef  ___STEAM_BRIDGE_CORE_H__
#define  ___STEAM_BRIDGE_CORE_H__

#include <deque>
#include <tr1/unordered_map>

class CCallbackBase;

class SteamAPIContext
{
  public:
    SteamAPIContext(int appid);
    ~SteamAPIContext();

    class ISteamUser                *getSteamUser()
      { return steamUser; }
    class ISteamFriends             *getSteamFriends()
      { return steamFriends; }
    class ISteamUtils               *getSteamUtils()
      { return steamUtils; }
    class ISteamMatchmaking         *getSteamMatchmaking()
      { return steamMatchmaking; }
    class ISteamUserStats           *getSteamUserStats()
      { return steamUserStats; }
    class ISteamApps                *getSteamApps()
      { return steamApps; }
    class ISteamMatchmakingServers  *getSteamMatchmakingServers()
      { return steamMatchmakingServers; }
    class ISteamNetworking          *getSteamNetworking()
      { return steamNetworking; }
    class ISteamRemoteStorage       *getSteamRemoteStorage()
      { return steamRemoteStorage; }
    class ISteamScreenshots         *getSteamScreenshots()
      { return steamScreenshots; }
    class ISteamHTTP                *getSteamHTTP()
      { return steamHTTP; }
    class ISteamUnifiedMessages     *getSteamUnifiedMessages() 
      { return steamUnifiedMessages; }


    void addCallback(CCallbackBase *wrapper, CCallbackBase *reference);
    CCallbackBase *getCallback(CCallbackBase *reference);
    void removeCallback(CCallbackBase *reference);

  private:
    int appid;

    std::deque<CCallbackBase *> callbacks;
    std::tr1::unordered_map<CCallbackBase *, CCallbackBase *> references;

    class ISteamUser                *steamUser;
    class ISteamFriends             *steamFriends;
    class ISteamUtils               *steamUtils;
    class ISteamMatchmaking         *steamMatchmaking;
    class ISteamUserStats           *steamUserStats;
    class ISteamApps                *steamApps;
    class ISteamMatchmakingServers  *steamMatchmakingServers;
    class ISteamNetworking          *steamNetworking;
    class ISteamRemoteStorage       *steamRemoteStorage;
    class ISteamScreenshots         *steamScreenshots;
    class ISteamHTTP                *steamHTTP;
    class ISteamUnifiedMessages     *steamUnifiedMessages;
};

extern SteamAPIContext *context;

#endif //___STEAM_BRIDGE_CORE_H__

