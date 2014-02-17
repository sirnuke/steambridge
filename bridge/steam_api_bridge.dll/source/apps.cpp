// apps.cpp - Implements various functions related to the ISteamApps class
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
  WINE_TRACE("(%p," TRACE ")\n", steamApps, ##__VA_ARGS__); \
  if (!steamApps) __ABORT("NULL steamApps pointer!"); \
  return steamApps->API(__VA_ARGS__); \
}

extern "C"
{

ISteamApps *SteamApps_()
{
  WINE_TRACE("\n");
  if (!state)
  {
    WINE_ERR("NULL internal state (init not called?)\n");
    return NULL;
  }
  return state->getSteamApps();
}

bool SteamApps_BIsSubscribed(ISteamApps *steamApps)
  _THIN_WRAPPER(BIsSubscribed, "")

bool SteamApps_BIsLowViolence(ISteamApps *steamApps)
  _THIN_WRAPPER(BIsLowViolence, "")

bool SteamApps_BIsCybercafe(ISteamApps *steamApps)
  _THIN_WRAPPER(BIsCybercafe, "")

bool SteamApps_BIsVACBanned(ISteamApps *steamApps)
  _THIN_WRAPPER(BIsVACBanned, "")

const char *SteamApps_GetCurrentGameLanguage(ISteamApps *steamApps)
  _THIN_WRAPPER(GetCurrentGameLanguage, "")

const char *SteamApps_GetAvailableGameLanguages(ISteamApps *steamApps)
  _THIN_WRAPPER(GetAvailableGameLanguages, "")

bool SteamApps_BIsSubscribedApp(ISteamApps *steamApps, AppId_t appId)
  _THIN_WRAPPER(BIsSubscribedApp, "%u", appId)

bool SteamApps_BIsDlcInstalled(ISteamApps *steamApps, AppId_t appID)
  _THIN_WRAPPER(BIsDlcInstalled, "%u", appID)

uint32 SteamApps_GetEarliestPurchaseUnixTime(ISteamApps *steamApps, AppId_t nAppID)
  _THIN_WRAPPER(GetEarliestPurchaseUnixTime, "%u", nAppID)

bool SteamApps_BIsSubscribedFromFreeWeekend(ISteamApps *steamApps)
  _THIN_WRAPPER(BIsSubscribedFromFreeWeekend, "")

int SteamApps_GetDLCCount(ISteamApps *steamApps)
  _THIN_WRAPPER(GetDLCCount, "")

bool SteamApps_BGetDLCDataByIndex(ISteamApps *steamApps, int iDLC, AppId_t *pAppID,
    bool *pbAvailable, char *pchName, int cchNameBufferSize)
  _THIN_WRAPPER(BGetDLCDataByIndex, "%i,%p,%p,%p,%i", iDLC, pAppID, pbAvailable, pchName,
      cchNameBufferSize)

void SteamApps_InstallDLC(ISteamApps *steamApps, AppId_t nAppID)
  _THIN_WRAPPER(InstallDLC, "%u", nAppID)

void SteamApps_UninstallDLC(ISteamApps *steamApps, AppId_t nAppID)
  _THIN_WRAPPER(UninstallDLC, "%u", nAppID)

void SteamApps_RequestAppProofOfPurchaseKey(ISteamApps *steamApps, AppId_t nAppID)
  _THIN_WRAPPER(RequestAppProofOfPurchaseKey, "%u", nAppID)

bool SteamApps_GetCurrentBetaName(ISteamApps *steamApps, char *pchName, int cchNameBufferSize)
  _THIN_WRAPPER(GetCurrentBetaName, "%p,%i", pchName, cchNameBufferSize)

bool SteamApps_MarkContentCorrupt(ISteamApps *steamApps, bool bMissingFilesOnly)
  _THIN_WRAPPER(MarkContentCorrupt, "%i", bMissingFilesOnly)

uint32 SteamApps_GetInstalledDepots(ISteamApps *steamApps, DepotId_t *pvecDepots, uint32 cMaxDepots)
  _THIN_WRAPPER(GetInstalledDepots, "%p,%u", pvecDepots, cMaxDepots)

uint32 SteamApps_GetAppInstallDir(ISteamApps *steamApps, AppId_t appID, char *pchFolder,
    uint32 cchFolderBufferSize)
  _THIN_WRAPPER(GetAppInstallDir, "%u,%p,%u", appID, pchFolder, cchFolderBufferSize)

} // extern "C"

