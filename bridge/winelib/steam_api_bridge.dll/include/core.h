// core.h - Headers for the core API calls.

#ifndef  ___STEAM_BRIDGE_CORE_H__
#define  ___STEAM_BRIDGE_CORE_H__

#include <deque>
#include <string>
#include <tr1/unordered_map>

#define __DLSYM_GET(TYPE, VAR, NAME) \
  TYPE VAR = (TYPE)(dlsym(context->getSteamAPIHandle(), NAME)); \
  if (!VAR) __ABORT("unable to find the " #NAME " symbol in libsteam_api.so");

class CCallbackBase;

class SteamAPIContext
{
  public:
    SteamAPIContext();
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

    bool prepare(AppId_t appid);

    void addCallback(CCallbackBase *wrapper, CCallbackBase *reference);
    CCallbackBase *getCallback(CCallbackBase *reference);
    void removeCallback(CCallbackBase *reference);

    void *getSteamAPIHandle();

  private:
    void checkBridgeDirectory();
    void loadSteamAPI();
    void readConfiguration();
    bool saveConfiguration();

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

    void *steam_api_handle;

    AppId_t appid;

    std::deque<CCallbackBase *> callbacks;
    std::tr1::unordered_map<CCallbackBase *, CCallbackBase *> references;

    std::string steamBridgeRoot;

    bool disclaimer;
};

extern SteamAPIContext *context;

#endif //___STEAM_BRIDGE_CORE_H__

