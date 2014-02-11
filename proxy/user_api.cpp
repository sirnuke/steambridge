// user_api.cpp - Implements the user wrapper and various related APIs.
#include "stdafx.h"

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"
#include "user_api.h"

#include <steam_api_bridge.h>

SteamUserWrapper::SteamUserWrapper() : steamUser(NULL)
{
  __TRACE("(0x%p)", this);
  steamUser = steam_bridge_SteamUser();
  __LOG("Wrapping ISteamUser (0x%p) in (0x%p)", steamUser, this);
}

HSteamUser SteamUserWrapper::GetHSteamUser()
  __STUB("")

bool SteamUserWrapper::BLoggedOn()
{
  __TRACE("()");
  return steam_bridge_SteamUser_BLoggedOn(steamUser);
}

CSteamID SteamUserWrapper::GetSteamID()
{
  __TRACE("()");
  // TODO: There might be a bit of unnecessary copying here.
  CSteamID id;
  steam_bridge_SteamUser_GetSteamID(steamUser, &id);
  __LOG("Get steamid of %lu", id.id);
  return id;
}

int SteamUserWrapper::InitiateGameConnection(void *pAuthBlob,
    int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer,
    uint16 usPortServer, bool bSecure)
{
  __TRACE("(0x%p,%i,%lu,%u,%hu,%i)", pAuthBlob, cbMaxAuthBlob,
      steamIDGameServer.id, unIPServer, usPortServer, bSecure);

  return steam_bridge_SteamUser_InitiateGameConnection(steamUser, pAuthBlob,
      cbMaxAuthBlob, steamIDGameServer, unIPServer, usPortServer, bSecure);
}
  

void SteamUserWrapper::TerminateGameConnection(uint32 unIPServer,
    uint16 usPortServer)
{
  __TRACE("(%u,%hu)", unIPServer, usPortServer);

  return steam_bridge_SteamUser_TerminateGameConnection(steamUser, unIPServer,
      usPortServer);
}

void SteamUserWrapper::TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent,
    const char *pchExtraInfo)
  __STUB("(%llu,%i,\"%s\")", gameID, eAppUsageEvent, pchExtraInfo)

bool SteamUserWrapper::GetUserDataFolder(char *pchBuffer, int cubBuffer)
  __STUB("(\"%s\",%i)", pchBuffer, cubBuffer)

void SteamUserWrapper::StartVoiceRecording()
  __STUB("")

void SteamUserWrapper::StopVoiceRecording()
  __STUB("")

int SteamUserWrapper::GetAvailableVoice(uint32 *pcbCompressed,
    uint32 *pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate)
  __STUB("(0x%p,0x%p,%u)", pcbCompressed, pcbUncompressed,
      nUncompressedVoiceDesiredSampleRate)

int SteamUserWrapper::GetVoice(bool bWantCompressed, void *pDestBuffer,
    uint32 cbDestBufferSize, uint32 *nBytesWritten, bool bWantUncompressed,
    void *pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize,
    uint32 *nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate)
  __STUB("(%i,0x%p,%u,0x%p,%i,0x%p,%u,0x%p,%u)", bWantCompressed, pDestBuffer,
      cbDestBufferSize, nBytesWritten, bWantUncompressed,
      pUncompressedDestBuffer, cbUncompressedDestBufferSize,
      nUncompressBytesWritten, nUncompressedVoiceDesiredSampleRate)

int SteamUserWrapper::DecompressVoice(const void *pCompressed,
    uint32 cbCompressed, void *pDestBuffer, uint32 cbDestBufferSize,
    uint32 *nBytesWritten, uint32 nDesiredSampleRate)
  __STUB("(0x%p,%u,0x%p,%u,0x%p,%u)", pCompressed, cbCompressed, pDestBuffer,
      cbDestBufferSize, nBytesWritten, nDesiredSampleRate)

uint32 SteamUserWrapper::GetVoiceOptimalSampleRate()
  __STUB("")

HAuthTicket SteamUserWrapper::GetAuthSessionTicket(void *pTicket,
    int cbMaxTicket, uint32 *pcbTicket)
  __STUB("(0x%p,%i,0x%p)", pTicket, cbMaxTicket, pcbTicket)

int SteamUserWrapper::BeginAuthSession(const void *pAuthTicket,
    int cbAuthTicket, uint64 steamID)
  __STUB("(0x%p,%i,%lu)", pAuthTicket, cbAuthTicket, steamID)

void SteamUserWrapper::EndAuthSession(uint64 steamID)
  __STUB("(%lu)", steamID)

void SteamUserWrapper::CancelAuthTicket(HAuthTicket hAuthTicket)
  __STUB("(%u)", hAuthTicket)

int SteamUserWrapper::UserHasLicenseForApp(uint64 steamID, AppId_t appID)
  __STUB("(%lu,%u)", steamID, appID)

bool SteamUserWrapper::BIsBehindNAT()
  __STUB("")

void SteamUserWrapper::AdvertiseGame(uint64 steamIDGameServer,
    uint32 unIPServer, uint16 usPortServer)
  __STUB("(%lu,%u,%hu)", steamIDGameServer, unIPServer, usPortServer)

SteamAPICall_t SteamUserWrapper::RequestEncryptedAppTicket(
    void *pDataToInclude, int cbDataToInclude)
  __STUB("(0x%p,%i)", pDataToInclude, cbDataToInclude)

bool SteamUserWrapper::GetEncryptedAppTicket(void *pTicket, int cbMaxTicket,
    uint32 *pcbTicket)
  __STUB("(0x%p,%i,0x%p)", pTicket, cbMaxTicket, pcbTicket)

extern "C"
{

STEAM_API_PROXY_API void *SteamUser()
{
  __TRACE("()");
  return state.getSteamUser();
}

} // extern "C"

