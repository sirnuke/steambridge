// user_api.cpp - Implements the user wrapper and various related APIs.
#include "stdafx.h"

#include <steam_api_bridge.h>

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"
#include "user_api.h"


SteamUserWrapper::SteamUserWrapper() : isteamuser(NULL)
{
  isteamuser = (void *)(steam_bridge_SteamUser());
}

HSteamUser SteamUserWrapper::GetHSteamUser()
  __STUB__

bool SteamUserWrapper::BLoggedOn()
  __STUB__

uint64 SteamUserWrapper::GetSteamID()
  __STUB__

int SteamUserWrapper::InitiateGameConnection(void *pAuthBlob, int cbMaxAuthBlob, uint64 steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
  __STUB__

void SteamUserWrapper::TerminateGameConnection(uint32 unIPServer, uint16 usPortServer)
  __STUB__

void SteamUserWrapper::TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent, const char *pchExtraInfo)
  __STUB__

bool SteamUserWrapper::GetUserDataFolder(char *pchBuffer, int cubBuffer)
  __STUB__

void SteamUserWrapper::StartVoiceRecording()
  __STUB__

void SteamUserWrapper::StopVoiceRecording()
  __STUB__

int SteamUserWrapper::GetAvailableVoice(uint32 *pcbCompressed, uint32 *pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate)
  __STUB__

int SteamUserWrapper::GetVoice(bool bWantCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, bool bWantUncompressed, void *pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32 *nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate)
  __STUB__

int SteamUserWrapper::DecompressVoice(const void *pCompressed, uint32 cbCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, uint32 nDesiredSampleRate)
  __STUB__

uint32 SteamUserWrapper::GetVoiceOptimalSampleRate()
  __STUB__

HAuthTicket SteamUserWrapper::GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
  __STUB__

int SteamUserWrapper::BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, uint64 steamID)
  __STUB__

void SteamUserWrapper::EndAuthSession(uint64 steamID)
  __STUB__

void SteamUserWrapper::CancelAuthTicket(HAuthTicket hAuthTicket)
  __STUB__

int SteamUserWrapper::UserHasLicenseForApp(uint64 steamID, AppId_t appID)
  __STUB__

bool SteamUserWrapper::BIsBehindNAT()
  __STUB__

void SteamUserWrapper::AdvertiseGame(uint64 steamIDGameServer, uint32 unIPServer, uint16 usPortServer)
  __STUB__

SteamAPICall_t SteamUserWrapper::RequestEncryptedAppTicket(void *pDataToInclude, int cbDataToInclude)
  __STUB__

bool SteamUserWrapper::GetEncryptedAppTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
  __STUB__

extern "C"
{

STEAM_API_PROXY_API void *SteamUser()
{
  return state.getSteamUser();
}

} // extern "C"

