// user_api.cpp - Implements the user wrapper and various related APIs
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include "stdafx.h"

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"
#include "user_api.h"

#include <steam_api_bridge.h>

#define _THIN_WRAPPER(API, TRACE, ...) { \
  __TRACE("(" TRACE ")", ##__VA_ARGS__); \
  return SteamUser_  ##API(steamUser, ##__VA_ARGS__); \
}

SteamUserWrapper::SteamUserWrapper() : steamUser(NULL)
{
  __TRACE("(0x%p)", this);
  steamUser = SteamUser_();
  __LOG("Wrapping ISteamUser (0x%p) in (0x%p)", steamUser, this);
}

HSteamUser SteamUserWrapper::GetHSteamUser()
  _THIN_WRAPPER(GetHSteamUser, "")

bool SteamUserWrapper::BLoggedOn()
  _THIN_WRAPPER(BLoggedOn, "")

CSteamID SteamUserWrapper::GetSteamID()
{
  __TRACE("()");
  // TODO: There might be a bit of unnecessary copying here.
  CSteamID id;
  SteamUser_GetSteamID(steamUser, &id);
  __LOG("Get steamid of %llu", id.id);
  return id;
}

int SteamUserWrapper::InitiateGameConnection(void *pAuthBlob, int cbMaxAuthBlob,
    CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
  _THIN_WRAPPER(InitiateGameConnection, "0x%p,%i,%llu,%u,%hu,%i", pAuthBlob, cbMaxAuthBlob,
      steamIDGameServer, unIPServer, usPortServer, bSecure)
  

void SteamUserWrapper::TerminateGameConnection(uint32 unIPServer, uint16 usPortServer)
  _THIN_WRAPPER(TerminateGameConnection, "%u,%hu", unIPServer, usPortServer)

void SteamUserWrapper::TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent,
    const char *pchExtraInfo)
  _THIN_WRAPPER(TrackAppUsageEvent, "%llu,%i,\"%s\"", gameID, eAppUsageEvent, pchExtraInfo)

bool SteamUserWrapper::GetUserDataFolder(char *pchBuffer, int cubBuffer)
  _THIN_WRAPPER(GetUserDataFolder, "0x%p,%i", pchBuffer, cubBuffer)

void SteamUserWrapper::StartVoiceRecording()
  _THIN_WRAPPER(StartVoiceRecording, "")

void SteamUserWrapper::StopVoiceRecording()
  _THIN_WRAPPER(StopVoiceRecording, "")

EVoiceResult SteamUserWrapper::GetAvailableVoice(uint32 *pcbCompressed, uint32 *pcbUncompressed,
    uint32 nUncompressedVoiceDesiredSampleRate)
  _THIN_WRAPPER(GetAvailableVoice, "0x%p,0x%p,%u", pcbCompressed, pcbUncompressed,
      nUncompressedVoiceDesiredSampleRate)

// What do we want? Mooore variables!
EVoiceResult SteamUserWrapper::GetVoice(bool bWantCompressed, void *pDestBuffer,
    uint32 cbDestBufferSize, uint32 *nBytesWritten, bool bWantUncompressed,
    void *pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize,
    uint32 *nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate)
  _THIN_WRAPPER(GetVoice, "%i,0x%p,%u,0x%p,%i,0x%p,%u,0x%p,%u", bWantCompressed, pDestBuffer,
      cbDestBufferSize, nBytesWritten, bWantUncompressed, pUncompressedDestBuffer,
      cbUncompressedDestBufferSize, nUncompressBytesWritten, nUncompressedVoiceDesiredSampleRate)

EVoiceResult SteamUserWrapper::DecompressVoice(const void *pCompressed, uint32 cbCompressed,
    void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, uint32 nDesiredSampleRate)
  _THIN_WRAPPER(DecompressVoice, "0x%p,%u,0x%p,%u,0x%p,%u", pCompressed, cbCompressed, pDestBuffer,
      cbDestBufferSize, nBytesWritten, nDesiredSampleRate)

uint32 SteamUserWrapper::GetVoiceOptimalSampleRate()
  _THIN_WRAPPER(GetVoiceOptimalSampleRate, "")

HAuthTicket SteamUserWrapper::GetAuthSessionTicket(void *pTicket, int cbMaxTicket,
    uint32 *pcbTicket)
  _THIN_WRAPPER(GetAuthSessionTicket, "0x%p,%i,0x%p", pTicket, cbMaxTicket, pcbTicket)

EBeginAuthSessionResult SteamUserWrapper::BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
  _THIN_WRAPPER(BeginAuthSession, "0x%p,%i", pAuthTicket, cbAuthTicket, steamID)

void SteamUserWrapper::EndAuthSession(CSteamID steamID)
  _THIN_WRAPPER(EndAuthSession, "%llu", steamID)

void SteamUserWrapper::CancelAuthTicket(HAuthTicket hAuthTicket)
  _THIN_WRAPPER(CancelAuthTicket, "%u", hAuthTicket)

EUserHasLicenseForAppResult SteamUserWrapper::UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
  _THIN_WRAPPER(UserHasLicenseForApp, "%llu,%u", steamID, appID)

bool SteamUserWrapper::BIsBehindNAT()
  _THIN_WRAPPER(BIsBehindNAT, "")

void SteamUserWrapper::AdvertiseGame(CSteamID steamIDGameServer, uint32 unIPServer,
    uint16 usPortServer)
  _THIN_WRAPPER(AdvertiseGame, "%llu,%u,%hu", steamIDGameServer, unIPServer, usPortServer)

SteamAPICall_t SteamUserWrapper::RequestEncryptedAppTicket(void *pDataToInclude, int cbDataToInclude)
  _THIN_WRAPPER(RequestEncryptedAppTicket, "0x%p,%i", pDataToInclude, cbDataToInclude)

bool SteamUserWrapper::GetEncryptedAppTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
  _THIN_WRAPPER(GetEncryptedAppTicket, "0x%p,%i,0x%p", pTicket, cbMaxTicket, pcbTicket)

extern "C"
{

STEAM_API_PROXY_API void *SteamUser()
{
  __TRACE("()");
  return state.getSteamUser();
}

} // extern "C"

