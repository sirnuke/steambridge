// client_api.cpp - Source for the client_api & SteamClientWrapper

#include "stdafx.h"

#include "client_api.h"
#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"

#include <steam_api_bridge.h>

SteamClientWrapper::SteamClientWrapper() : steamClient(NULL)
{
  __TRACE("(this=0x%p)", this);
  steamClient = steam_bridge_SteamClient();
  __LOG("Wrapping ISteamClient (0x%p) into (0x%p)", steamClient, this);
}

HSteamPipe SteamClientWrapper::CreateSteamPipe()
  __STUB("")

bool SteamClientWrapper::BReleaseSteamPipe(HSteamPipe hSteamPipe)
  __STUB("(%i)", hSteamPipe)

HSteamUser SteamClientWrapper::ConnectToGlobalUser(HSteamPipe hSteamPipe)
  __STUB("(%i)", hSteamPipe)

// HSteamUser ... (HSteamPipe *, EAccountType)
HSteamUser SteamClientWrapper::CreateLocalUser(HSteamPipe *phSteamPipe,
    int eAccountType)
  __STUB("(0x%p,%i)", phSteamPipe, eAccountType)

void SteamClientWrapper::ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser)
  __STUB("(%i,%i)", hSteamPipe, hUser)

ISteamUser *SteamClientWrapper::GetISteamUser(HSteamUser hSteamUser,
    HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

ISteamGameServer *SteamClientWrapper::GetISteamGameServer(HSteamUser hSteamUser,
    HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

void SteamClientWrapper::SetLocalIPBinding(uint32 unIP, uint16 usPort)
  __STUB("(%u,%hu)", unIP, usPort)

ISteamFriends *SteamClientWrapper::GetISteamFriends(HSteamUser hSteamUser,
    HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

ISteamUtils *SteamClientWrapper::GetISteamUtils(HSteamPipe hSteamPipe,
    const char *pchVersion)
  __STUB("(%i,\"%s\")", hSteamPipe, pchVersion)

ISteamMatchmaking *SteamClientWrapper::GetISteamMatchmaking(
    HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

ISteamMatchmakingServers *SteamClientWrapper::GetISteamMatchmakingServers(
    HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

void *SteamClientWrapper::GetISteamGenericInterface(HSteamUser hSteamUser,
    HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

ISteamUserStats *SteamClientWrapper::GetISteamUserStats(HSteamUser hSteamUser,
    HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

ISteamGameServerStats *SteamClientWrapper::GetISteamGameServerStats(
    HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

ISteamApps *SteamClientWrapper::GetISteamApps(HSteamUser hSteamUser,
    HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

ISteamNetworking *SteamClientWrapper::GetISteamNetworking(HSteamUser hSteamUser,
    HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

ISteamRemoteStorage *SteamClientWrapper::GetISteamRemoteStorage(
    HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

ISteamScreenshots *SteamClientWrapper::GetISteamScreenshots(
    HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

void SteamClientWrapper::RunFrame()
  __STUB("")

uint32 SteamClientWrapper::GetIPCCallCount()
  __STUB("")

// Yeah, I don't think this function will work quite right
void SteamClientWrapper::SetWarningMessageHook(
    SteamAPIWarningMessageHook_t pFunction)
{
  __TRACE("(0x%p)", pFunction);
  steam_bridge_SteamClient_SetWarningMessageHook(steamClient, pFunction);
}

bool SteamClientWrapper::BShutdownIfAllPipesClosed()
  __STUB("")

ISteamHTTP *SteamClientWrapper::GetISteamHTTP(HSteamUser hSteamUser,
    HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

ISteamUnifiedMessages *SteamClientWrapper::GetISteamUnifiedMessages(
    HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion)
  __STUB("(%i,%i,\"%s\")", hSteamUser, hSteamPipe, pchVersion)

extern "C"
{

STEAM_API_PROXY_API void *SteamClient()
{
  __TRACE("()");
  return state.getSteamClient();
}

} // extern "C"
