// user_api.cpp - Implements the user wrapper and various related APIs.
#include "stdafx.h"

#include <steam_api_bridge.h>

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"

class SteamUserWrapper
{
  public:
    SteamUserWrapper();

    virtual HSteamUser GetHSteamUser();
    virtual bool BLoggedOn();

    // CSteamID is a class that 'wraps' around a steamID and other
    // such nonsense.  It's probablllyyy safe to just return a uint64,
    // at least on this side of the bridge.  At a glance, most everything
    // of important is inlined, and since it's a set 64 bits without any
    // real magic, it probably isn't necessary to implement anything.

    // CSteamID ... ()
    virtual uint64 GetSteamID();

    // int ... (void *, int, CSteamID, uint32, uint16, bool)
    virtual int InitiateGameConnection(void *pAuthBlob, int cbMaxAuthBlob, uint64 steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure);
    virtual void TerminateGameConnection(uint32 unIPServer, uint16 usPortServer);

    // CGameID appears to be similar to CSteamID, except for gameIDs.
    // It's a set 128 bits long, so can probably just pass a uint128 around.
    // void ... (CGameID, int, const char * = "")
    virtual void TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent, const char *pchExtraInfo = "");
    virtual bool GetUserDataFolder(char *pchBuffer, int cubBuffer);

    virtual void StartVoiceRecording();
    virtual void StopVoiceRecording();

    // EVoiceResult ... (uint32 *, uint32 *, uint32)
    virtual int GetAvailableVoice(uint32 *pcbCompressed, uint32 *pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate);

    // EVoiceResult ... (bool, void *, uint32, uint32 *, bool, void *, uint32, uint32 *, uint32)
    virtual int GetVoice(bool bWantCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, bool bWantUncompressed, void *pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32 *nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate);

    // EVoiceResult ... (const void *, uint32, void *, uint32, uint32 *, uint32)
    virtual int DecompressVoice(const void *pCompressed, uint32 cbCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten, uint32 nDesiredSampleRate);

    virtual uint32 GetVoiceOptimalSampleRate();
    virtual HAuthTicket GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket);

    // EBeginAuthSessionResult ... (const void *, int, CSteamID)
    virtual int BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, uint64 steamID);

    // void ... (CSteamID)
    virtual void EndAuthSession(uint64 steamID);

    virtual void CancelAuthTicket(HAuthTicket hAuthTicket);

    // EUserHasLicenseForAppResult ... (CSteamID, AppId_t)
    virtual int UserHasLicenseForApp(uint64 steamID, AppId_t appID);

    virtual bool BIsBehindNAT();

    // void ... (CSteamID, uint32, uint16)
    virtual void AdvertiseGame(uint64 steamIDGameServer, uint32 unIPServer, uint16 usPortServer);

    virtual SteamAPICall_t RequestEncryptedAppTicket(void *pDataToInclude, int cbDataToInclude);
    virtual bool GetEncryptedAppTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket);

  private:
    void *isteamuser;
};

SteamUserWrapper::SteamUserWrapper()
{
  // TODO: This wraps around a hardcoded SteamUser version for the
  //       AudioSurf demo
  isteamuser = (void *)(steam_bridge_SteamUser("SteamUser016"));
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
  SteamUserWrapper *user = new SteamUserWrapper();
  return user;
}

} // extern "C"

