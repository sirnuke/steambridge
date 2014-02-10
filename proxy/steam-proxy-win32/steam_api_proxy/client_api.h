// client_api.h - Header for the client_api & SteamClientWrapper

#pragma once

#include "types.h"

class SteamClientWrapper
{
  public:

    SteamClientWrapper();

    virtual HSteamPipe CreateSteamPipe();

    virtual bool BReleaseSteamPipe(HSteamPipe hSteamPipe);

    virtual HSteamUser ConnectToGlobalUser(HSteamPipe hSteamPipe);

    // HSteamUser ... (HSteamPipe *, EAccountType)
    virtual HSteamUser CreateLocalUser(HSteamPipe *phSteamPipe,
        int eAccountType);

    virtual void ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser);

    virtual ISteamUser *GetISteamUser(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual ISteamGameServer *GetISteamGameServer(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual void SetLocalIPBinding(uint32 unIP, uint16 usPort); 

    virtual ISteamFriends *GetISteamFriends(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual ISteamUtils *GetISteamUtils(HSteamPipe hSteamPipe,
        const char *pchVersion);

    virtual ISteamMatchmaking *GetISteamMatchmaking(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual ISteamMatchmakingServers *GetISteamMatchmakingServers(
        HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);

    virtual void *GetISteamGenericInterface(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual ISteamUserStats *GetISteamUserStats(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual ISteamGameServerStats *GetISteamGameServerStats(
        HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);

    virtual ISteamApps *GetISteamApps(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual ISteamNetworking *GetISteamNetworking(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual ISteamRemoteStorage *GetISteamRemoteStorage(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual ISteamScreenshots *GetISteamScreenshots(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual void RunFrame();

    virtual uint32 GetIPCCallCount();

    virtual void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction);

    virtual bool BShutdownIfAllPipesClosed();

    virtual ISteamHTTP *GetISteamHTTP(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual ISteamUnifiedMessages *GetISteamUnifiedMessages(
        HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);

  private:
    ISteamClient *steamClient;

};
