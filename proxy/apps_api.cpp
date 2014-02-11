// apps_api.cpp - Implements the apps wrapper and various related APIs.

#include "stdafx.h"

#include "apps_api.h"
#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"

#include <steam_api_bridge.h>

SteamAppsWrapper::SteamAppsWrapper()
{
  __TRACE("(this=0x%p)", this);
  steamApps = steam_bridge_SteamApps();
  __LOG("Wrapped steamApps (0x%p) in (0x%p)", steamApps, this);
}

bool SteamAppsWrapper::BIsSubscribed()
  __STUB("")

bool SteamAppsWrapper::BIsLowViolence()
  __STUB("")

bool SteamAppsWrapper::BIsCybercafe()
  __STUB("")

bool SteamAppsWrapper::BIsVACBanned()
  __STUB("")

const char *SteamAppsWrapper::GetCurrentGameLanguage()
{
  __TRACE("()");
  return steam_bridge_SteamApps_GetCurrentGameLanguage(steamApps);
}

const char *SteamAppsWrapper::GetAvailableGameLanguages()
  __STUB("")

bool SteamAppsWrapper::BIsSubscribedApp(AppId_t appId)
{
  __TRACE("(%u)", appId);
  return steam_bridge_SteamApps_BIsSubscribedApp(steamApps, appId);
}

bool SteamAppsWrapper::BIsDlcInstalled(AppId_t appId)
  __STUB("(%u)", appId)

uint32 SteamAppsWrapper::GetEarliestPurchaseUnixTime(AppId_t nAppID)
  __STUB("(%u)", nAppID)

bool SteamAppsWrapper::BIsSubscribedFromFreeWeekend()
  __STUB("")

int SteamAppsWrapper::GetDLCCount()
  __STUB("")

bool SteamAppsWrapper::BGetDLCDataByIndex(int iDLC, AppId_t *pAppID,
    bool *pbAvailable, char *pchName, int cchNameBufferSize)
  __STUB("(%i,0x%p,0x%p,\"%s\",%i)", iDLC, pAppID, pbAvailable, pchName,
      cchNameBufferSize)

void SteamAppsWrapper::InstallDLC(AppId_t nAppID)
  __STUB("(%u)", nAppID)

void SteamAppsWrapper::UninstallDLC(AppId_t nAppID)
  __STUB("(%u)", nAppID)

void SteamAppsWrapper::RequestAppProofOfPurchaseKey(AppId_t nAppID)
  __STUB("(%u)", nAppID)

bool SteamAppsWrapper::GetCurrentBetaName(char *pchName, int cchNameBufferSize)
  __STUB("(\"%s\",%i)", pchName, cchNameBufferSize)

bool SteamAppsWrapper::MarkContentCorrupt(bool bMissingFilesOnly)
  __STUB("(%i)", bMissingFilesOnly)

uint32 SteamAppsWrapper::GetInstalledDepots(DepotId_t *pvecDepots,
    uint32 cMaxDepots)
  __STUB("(0x%p,%u)", pvecDepots, cMaxDepots)

uint32 SteamAppsWrapper::GetAppInstallDir(AppId_t appID, char *pchFolder,
    uint32 cchFolderBufferSize)
  __STUB("(%u,0x%p,%u)", appID, pchFolder, cchFolderBufferSize)

extern "C"
{

STEAM_API_PROXY_API void *SteamApps()
{ 
  __TRACE("()");
  return state.getSteamApps();
}

} // extern "C"

