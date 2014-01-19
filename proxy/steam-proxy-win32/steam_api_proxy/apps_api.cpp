// apps_api.cpp - Implements the apps wrapper and various related APIs.

#include "stdafx.h"

#include <steam_api_bridge.h>

#include "apps_api.h"
#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"

SteamAppsWrapper::SteamAppsWrapper()
{
  steamApps = steam_bridge_SteamApps();
}

bool SteamAppsWrapper::BIsSubscribed()
  __STUB__

bool SteamAppsWrapper::BIsLowViolence()
  __STUB__

bool SteamAppsWrapper::BIsCybercafe()
  __STUB__

bool SteamAppsWrapper::BIsVACBanned()
  __STUB__

const char *SteamAppsWrapper::GetCurrentGameLanguage()
  __STUB__

const char *SteamAppsWrapper::GetAvailableGameLanguages()
  __STUB__

bool SteamAppsWrapper::BIsSubscribedApp(AppId_t appID)
  __STUB__

bool SteamAppsWrapper::BIsDlcInstalled(AppId_t appID)
  __STUB__

uint32 SteamAppsWrapper::GetEarliestPurchaseUnixTime(AppId_t nAppID)
  __STUB__

bool SteamAppsWrapper::BIsSubscribedFromFreeWeekend()
  __STUB__

int SteamAppsWrapper::GetDLCCount()
  __STUB__

bool SteamAppsWrapper::BGetDLCDataByIndex(int iDLC, AppId_t *pAppID, bool *pbAvailable, char *pchName, int cchNameBufferSize)
  __STUB__

void SteamAppsWrapper::InstallDLC(AppId_t nAppID)
  __STUB__

void SteamAppsWrapper::UninstallDLC(AppId_t nAppID)
  __STUB__

void SteamAppsWrapper::RequestAppProofOfPurchaseKey(AppId_t nAppID)
  __STUB__

bool SteamAppsWrapper::GetCurrentBetaName(char *pchName, int cchNameBufferSize)
  __STUB__

bool SteamAppsWrapper::MarkContentCorrupt(bool bMissingFilesOnly)
  __STUB__

uint32 SteamAppsWrapper::GetInstalledDepots(DepotId_t *pvecDepots, uint32 cMaxDepots)
  __STUB__

uint32 SteamAppsWrapper::GetAppInstallDir(AppId_t appID, char *pchFolder, uint32 cchFolderBufferSize)
  __STUB__

extern "C"
{

STEAM_API_PROXY_API void *SteamApps()
{ 
  return state.getSteamApps();
}

} // extern "C"

