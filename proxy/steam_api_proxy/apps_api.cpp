// apps_api.cpp - Implements the apps wrapper and various related APIs
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include "stdafx.h"

#include "apps_api.h"
#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"

#include <steam_api_bridge.h>

#define _THIN_WRAPPER(API, TRACE, ...) { \
  __TRACE("" TRACE "", ##__VA_ARGS__); \
  return SteamApps_  ##API(steamApps, ##__VA_ARGS__); \
}

SteamAppsWrapper::SteamAppsWrapper()
{
  __TRACE("(this=0x%p)", this);
  steamApps = SteamApps_();
  __LOG("Wrapped steamApps (0x%p) in (0x%p)", steamApps, this);
}

bool SteamAppsWrapper::BIsSubscribed()
  _THIN_WRAPPER(BIsSubscribed, "")

bool SteamAppsWrapper::BIsLowViolence()
  _THIN_WRAPPER(BIsLowViolence, "")

bool SteamAppsWrapper::BIsCybercafe()
  _THIN_WRAPPER(BIsCybercafe, "")

bool SteamAppsWrapper::BIsVACBanned()
  _THIN_WRAPPER(BIsVACBanned, "")

const char *SteamAppsWrapper::GetCurrentGameLanguage()
  _THIN_WRAPPER(GetCurrentGameLanguage, "")

const char *SteamAppsWrapper::GetAvailableGameLanguages()
  _THIN_WRAPPER(GetAvailableGameLanguages, "")

bool SteamAppsWrapper::BIsSubscribedApp(AppId_t appId)
  _THIN_WRAPPER(BIsSubscribedApp, "%u", appId)

bool SteamAppsWrapper::BIsDlcInstalled(AppId_t appId)
  _THIN_WRAPPER(BIsDlcInstalled, "%u", appId)

uint32 SteamAppsWrapper::GetEarliestPurchaseUnixTime(AppId_t nAppID)
  _THIN_WRAPPER(GetEarliestPurchaseUnixTime, "%u", nAppID)

bool SteamAppsWrapper::BIsSubscribedFromFreeWeekend()
  _THIN_WRAPPER(BIsSubscribedFromFreeWeekend, "")

int SteamAppsWrapper::GetDLCCount()
  _THIN_WRAPPER(GetDLCCount, "")

bool SteamAppsWrapper::BGetDLCDataByIndex(int iDLC, AppId_t *pAppID,
    bool *pbAvailable, char *pchName, int cchNameBufferSize)
  _THIN_WRAPPER(BGetDLCDataByIndex, "%i,0x%p,0x%p,\"%s\",%i", iDLC, pAppID, pbAvailable,
      pchName, cchNameBufferSize)

void SteamAppsWrapper::InstallDLC(AppId_t nAppID)
  _THIN_WRAPPER(InstallDLC, "%u", nAppID)

void SteamAppsWrapper::UninstallDLC(AppId_t nAppID)
  _THIN_WRAPPER(UninstallDLC, "%u", nAppID)

void SteamAppsWrapper::RequestAppProofOfPurchaseKey(AppId_t nAppID)
  _THIN_WRAPPER(RequestAppProofOfPurchaseKey, "%u", nAppID)

bool SteamAppsWrapper::GetCurrentBetaName(char *pchName, int cchNameBufferSize)
  _THIN_WRAPPER(GetCurrentBetaName, "\"%s\",%i", pchName, cchNameBufferSize)

bool SteamAppsWrapper::MarkContentCorrupt(bool bMissingFilesOnly)
  _THIN_WRAPPER(MarkContentCorrupt, "%i", bMissingFilesOnly)

uint32 SteamAppsWrapper::GetInstalledDepots(DepotId_t *pvecDepots,
    uint32 cMaxDepots)
  _THIN_WRAPPER(GetInstalledDepots, "0x%p,%u", pvecDepots, cMaxDepots)

uint32 SteamAppsWrapper::GetAppInstallDir(AppId_t appID, char *pchFolder,
    uint32 cchFolderBufferSize)
  _THIN_WRAPPER(GetAppInstallDir, "%u,0x%p,%u", appID, pchFolder, cchFolderBufferSize)

extern "C"
{

STEAM_API_PROXY_API void *SteamApps()
{ 
  __TRACE("");
  return state.getSteamApps();
}

} // extern "C"

