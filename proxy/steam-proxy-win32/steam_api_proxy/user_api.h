// user_api.h - Header for the user_api code (specifically SteamUserWrapper)

#pragma once

#include <string>

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
    virtual CSteamID GetSteamID();

    // int ... (void *, int, CSteamID, uint32, uint16, bool)
    virtual int InitiateGameConnection(void *pAuthBlob, int cbMaxAuthBlob,
        uint64 steamIDGameServer, uint32 unIPServer, uint16 usPortServer,
        bool bSecure);
    virtual void TerminateGameConnection(uint32 unIPServer,
        uint16 usPortServer);

    // CGameID appears to be similar to CSteamID, except for gameIDs.
    // It's a set 128 bits long, so can probably just pass a uint128 around.
    // void ... (CGameID, int, const char * = "")
    virtual void TrackAppUsageEvent(CGameID gameID, int eAppUsageEvent,
        const char *pchExtraInfo = "");
    virtual bool GetUserDataFolder(char *pchBuffer, int cubBuffer);

    virtual void StartVoiceRecording();
    virtual void StopVoiceRecording();

    // EVoiceResult ... (uint32 *, uint32 *, uint32)
    virtual int GetAvailableVoice(uint32 *pcbCompressed,
        uint32 *pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate);

    // EVoiceResult ... (bool, void *, uint32, uint32 *, bool, void *, uint32,
    //                   uint32 *, uint32)
    virtual int GetVoice(bool bWantCompressed, void *pDestBuffer,
        uint32 cbDestBufferSize, uint32 *nBytesWritten, bool bWantUncompressed,
        void *pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize,
        uint32 *nUncompressBytesWritten,
        uint32 nUncompressedVoiceDesiredSampleRate);

    // EVoiceResult ... (const void *, uint32, void *, uint32, uint32 *, uint32)
    virtual int DecompressVoice(const void *pCompressed, uint32 cbCompressed,
        void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten,
        uint32 nDesiredSampleRate);

    virtual uint32 GetVoiceOptimalSampleRate();
    virtual HAuthTicket GetAuthSessionTicket(void *pTicket, int cbMaxTicket,
        uint32 *pcbTicket);

    // EBeginAuthSessionResult ... (const void *, int, CSteamID)
    virtual int BeginAuthSession(const void *pAuthTicket, int cbAuthTicket,
        uint64 steamID);

    // void ... (CSteamID)
    virtual void EndAuthSession(uint64 steamID);

    virtual void CancelAuthTicket(HAuthTicket hAuthTicket);

    // EUserHasLicenseForAppResult ... (CSteamID, AppId_t)
    virtual int UserHasLicenseForApp(uint64 steamID, AppId_t appID);

    virtual bool BIsBehindNAT();

    // void ... (CSteamID, uint32, uint16)
    virtual void AdvertiseGame(uint64 steamIDGameServer, uint32 unIPServer,
        uint16 usPortServer);

    virtual SteamAPICall_t RequestEncryptedAppTicket(void *pDataToInclude,
        int cbDataToInclude);
    virtual bool GetEncryptedAppTicket(void *pTicket, int cbMaxTicket,
        uint32 *pcbTicket);

  private:
    // TODO: This function technically changes the size/composition of
    //       this class from ISteamUser reference that is expected.
    //       If client code isn't really checking the sizes of everything,
    //       it's not really an issue.
    class ISteamUser *steamUser;
};
