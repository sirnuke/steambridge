// apps_api.h - Header for the apps_api code

#pragma once

#include <string>

#include "types.h"


class SteamAppsWrapper
{
  public:
    SteamAppsWrapper();

    virtual bool BIsSubscribed();
    virtual bool BIsLowViolence();
    virtual bool BIsCybercafe();
    virtual bool BIsVACBanned();
    virtual const char *GetCurrentGameLanguage();
    virtual const char *GetAvailableGameLanguages();

    virtual bool BIsSubscribedApp(AppId_t appID);

    virtual bool BIsDlcInstalled(AppId_t appID);

    virtual uint32 GetEarliestPurchaseUnixTime(AppId_t nAppID);

    virtual bool BIsSubscribedFromFreeWeekend();

    virtual int GetDLCCount();

    virtual bool BGetDLCDataByIndex(int iDLC, AppId_t *pAppID, bool *pbAvailable, char *pchName, int cchNameBufferSize);

    // These two functions, by nature, probably can't be support
    virtual void InstallDLC(AppId_t nAppID);
    virtual void UninstallDLC(AppId_t nAppID);

    virtual void RequestAppProofOfPurchaseKey(AppId_t nAppID);

    virtual bool GetCurrentBetaName(char *pchName, int cchNameBufferSize);

    // This function probably can't be handled correctly
    virtual bool MarkContentCorrupt(bool bMissingFilesOnly);

    virtual uint32 GetInstalledDepots(DepotId_t *pvecDepots, uint32 cMaxDepots);

    virtual uint32 GetAppInstallDir(AppId_t appID, char *pchFolder, uint32 cchFolderBufferSize);

  private:
    class ISteamApps *steamApps;
};

