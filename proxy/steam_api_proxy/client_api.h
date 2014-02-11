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

    virtual class ISteamUser *GetISteamUser(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual class ISteamGameServer *GetISteamGameServer(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual void SetLocalIPBinding(uint32 unIP, uint16 usPort); 

    virtual class ISteamFriends *GetISteamFriends(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual class ISteamUtils *GetISteamUtils(HSteamPipe hSteamPipe,
        const char *pchVersion);

    virtual class ISteamMatchmaking *GetISteamMatchmaking(
        HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);

    virtual class ISteamMatchmakingServers *GetISteamMatchmakingServers(
        HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);

    virtual void *GetISteamGenericInterface(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual class ISteamUserStats *GetISteamUserStats(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual class ISteamGameServerStats *GetISteamGameServerStats(
        HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);

    virtual class ISteamApps *GetISteamApps(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual class ISteamNetworking *GetISteamNetworking(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual class ISteamRemoteStorage *GetISteamRemoteStorage(
        HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);

    virtual class ISteamScreenshots *GetISteamScreenshots(
        HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);

    virtual void RunFrame();

    virtual uint32 GetIPCCallCount();

    virtual void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction);

    virtual bool BShutdownIfAllPipesClosed();

    virtual class ISteamHTTP *GetISteamHTTP(HSteamUser hSteamUser,
        HSteamPipe hSteamPipe, const char *pchVersion);

    virtual class ISteamUnifiedMessages *GetISteamUnifiedMessages(
        HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion);

  private:
    class ISteamClient *steamClient;

};
