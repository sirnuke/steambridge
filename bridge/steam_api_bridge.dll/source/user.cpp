// user.cpp - Implements various functions related to the ISteamUser class
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include <cstdio>

#include <steam_api.h>

#define NOMINMAX
#include <wine/debug.h>

#include "api.h"
#include "logging.h"
#include "state.h"

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

#define _THIN_WRAPPER(API, TRACE, ...) { \
  WINE_TRACE("(%p," TRACE ")\n", steamUser, ##__VA_ARGS__); \
  if (!steamUser) __ABORT("NULL steamUser pointer!"); \
  return steamUser->API(__VA_ARGS__); \
}

extern "C"
{

ISteamUser *SteamUser_()
{
  WINE_TRACE("\n");
  if (!state)
  {
    WINE_ERR("NULL internal state (init not called?)\n");
    return NULL;
  }
  return state->getSteamUser();
}

HSteamUser SteamUser_GetHSteamUser(ISteamUser *steamUser)
  _THIN_WRAPPER(GetHSteamUser, "")

void SteamUser_GetSteamID(ISteamUser *steamUser, CSteamID *id)
{
  WINE_TRACE("(%p,%p)\n", steamUser, id);

  if (!steamUser) __ABORT("NULL steamUser pointer!");
  if (!id) __ABORT("NULL CSteamID result pointer!");

  *id = steamUser->GetSteamID();
  WINE_TRACE("Got steamUser ID of %llu\n", id);
}

bool SteamUser_BLoggedOn(ISteamUser *steamUser)
  _THIN_WRAPPER(BLoggedOn, "")

int SteamUser_InitiateGameConnection(ISteamUser *steamUser, void *pAuthBlob, int cbMaxAuthBlob,
    CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
  _THIN_WRAPPER(InitiateGameConnection, "%p,%i,%llu,%u,%hu,%i", pAuthBlob, cbMaxAuthBlob,
      steamIDGameServer, unIPServer, usPortServer, bSecure)

void SteamUser_TerminateGameConnection(ISteamUser *steamUser, uint32 unIPServer,
    uint16 usPortServer)
  _THIN_WRAPPER(TerminateGameConnection, "%u,%hu", unIPServer, usPortServer)

void SteamUser_TrackAppUsageEvent(ISteamUser *steamUser, CGameID gameID, int eAppUsageEvent,
    const char *pchExtraInfo)
  _THIN_WRAPPER(TrackAppUsageEvent, "%llu,%i,\"%s\"", gameID, eAppUsageEvent, pchExtraInfo)

bool SteamUser_GetUserDataFolder(ISteamUser *steamUser, char *pchBuffer, int cubBuffer)
  _THIN_WRAPPER(GetUserDataFolder, "%p,%i", pchBuffer, cubBuffer)

void SteamUser_StartVoiceRecording(ISteamUser *steamUser)
  _THIN_WRAPPER(StartVoiceRecording, "");

void SteamUser_StopVoiceRecording(ISteamUser *steamUser)
  _THIN_WRAPPER(StopVoiceRecording, "");

EVoiceResult SteamUser_GetAvailableVoice(ISteamUser *steamUser, uint32 *pcbCompressed,
    uint32 *pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate)
  _THIN_WRAPPER(GetAvailableVoice, "%p,%p,%u", pcbCompressed, pcbUncompressed,
      nUncompressedVoiceDesiredSampleRate)

EVoiceResult SteamUser_GetVoice(ISteamUser *steamUser, bool bWantCompressed, void *pDestBuffer,
    uint32 cbDestBufferSize, uint32 *nBytesWritten, bool bWantUncompressed,
    void *pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize,
    uint32 *nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate)
  _THIN_WRAPPER(GetVoice, "%i,%p,%u,%p,%i,%p,%u,%p,%u", bWantCompressed, pDestBuffer,
      cbDestBufferSize, nBytesWritten, bWantUncompressed, pUncompressedDestBuffer,
      cbUncompressedDestBufferSize, nUncompressBytesWritten, nUncompressedVoiceDesiredSampleRate)

EVoiceResult SteamUser_DecompressVoice(ISteamUser *steamUser, const void *pCompressed,
    uint32 cbCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten,
    uint32 nDesiredSampleRate)
  _THIN_WRAPPER(DecompressVoice, "%p,%u,%p,%u,%p,%u", pCompressed, cbCompressed, pDestBuffer,
      cbDestBufferSize, nBytesWritten, nDesiredSampleRate)

uint32 SteamUser_GetVoiceOptimalSampleRate(ISteamUser *steamUser)
  _THIN_WRAPPER(GetVoiceOptimalSampleRate, "")

HAuthTicket SteamUser_GetAuthSessionTicket(ISteamUser *steamUser, void *pTicket, int cbMaxTicket,
    uint32 *pcbTicket)
  _THIN_WRAPPER(GetAuthSessionTicket, "%p,%i,%p", pTicket, cbMaxTicket, pcbTicket)

EBeginAuthSessionResult SteamUser_BeginAuthSession(ISteamUser *steamUser, const void *pAuthTicket,
    int cbAuthTicket, CSteamID steamID)
  _THIN_WRAPPER(BeginAuthSession, "%p,%i,%llu", pAuthTicket, cbAuthTicket, steamID)

void SteamUser_EndAuthSession(ISteamUser *steamUser, CSteamID steamID)
  _THIN_WRAPPER(EndAuthSession, "%llu", steamID)

void SteamUser_CancelAuthTicket(ISteamUser *steamUser, HAuthTicket hAuthTicket)
  _THIN_WRAPPER(CancelAuthTicket, "%u", hAuthTicket)

EUserHasLicenseForAppResult SteamUser_UserHasLicenseForApp(ISteamUser *steamUser, CSteamID steamID,
    AppId_t appID)
  _THIN_WRAPPER(UserHasLicenseForApp, "%llu,%u", steamID, appID)

bool SteamUser_BIsBehindNAT(ISteamUser *steamUser)
  _THIN_WRAPPER(BIsBehindNAT, "")

void SteamUser_AdvertiseGame(ISteamUser *steamUser, CSteamID steamIDGameServer, uint32 unIPServer,
    uint16 usPortServer)
  _THIN_WRAPPER(AdvertiseGame, "%llu,%u,%hu", steamIDGameServer, unIPServer, usPortServer)

SteamAPICall_t SteamUser_RequestEncryptedAppTicket(ISteamUser *steamUser, void *pDataToInclude,
    int cbDataToInclude)
  _THIN_WRAPPER(RequestEncryptedAppTicket, "%p,%i", pDataToInclude, cbDataToInclude)

bool SteamUser_GetEncryptedAppTicket(ISteamUser *steamUser, void *pTicket, int cbMaxTicket,
    uint32 *pcbTicket)
  _THIN_WRAPPER(GetEncryptedAppTicket, "%p,%i,%p", pTicket, cbMaxTicket, pcbTicket)

} // extern "C"

