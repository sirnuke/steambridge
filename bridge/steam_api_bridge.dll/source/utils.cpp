// utils.cpp - Implements various functions related to the ISteamUtils class
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
  WINE_TRACE("(%p," TRACE ")\n", steamUtils, ##__VA_ARGS__); \
  if (!steamUtils) __ABORT("NULL steamUtils pointer!"); \
  return steamUtils->API(__VA_ARGS__); \
}

extern "C"
{

ISteamUtils *SteamUtils_()
{
  WINE_TRACE("\n");
  if (!state)
  {
    WINE_ERR("NULL internal state (init not caled?)\n");
    return NULL;
  }
  return state->getSteamUtils();
}

uint32 SteamUtils_GetSecondsSinceAppActive(ISteamUtils *steamUtils)
  _THIN_WRAPPER(GetSecondsSinceAppActive, "")

uint32 SteamUtils_GetSecondsSinceComputerActive(ISteamUtils *steamUtils)
  _THIN_WRAPPER(GetSecondsSinceComputerActive, "")

EUniverse SteamUtils_GetConnectedUniverse(ISteamUtils *steamUtils)
  _THIN_WRAPPER(GetConnectedUniverse, "")

uint32 SteamUtils_GetServerRealTime(ISteamUtils *steamUtils)
  _THIN_WRAPPER(GetServerRealTime, "")

const char *SteamUtils_GetIPCountry(ISteamUtils *steamUtils)
  _THIN_WRAPPER(GetIPCountry, "")

bool SteamUtils_GetImageSize(ISteamUtils *steamUtils, int iImage, uint32 *pnWidth, uint32 *pnHeight)
  _THIN_WRAPPER(GetImageSize, "%i,%p,%p", iImage, pnWidth, pnHeight)

bool SteamUtils_GetImageRGBA(ISteamUtils *steamUtils, int iImage, uint8 *pubDest,
    int nDestBufferSize)
  _THIN_WRAPPER(GetImageRGBA, "%i,%p,%i", iImage, pubDest, nDestBufferSize)

bool SteamUtils_GetCSERIPPort(ISteamUtils *steamUtils, uint32 *unIP, uint16 *usPort)
  _THIN_WRAPPER(GetCSERIPPort, "%p,%p", unIP, usPort)

uint8 SteamUtils_GetCurrentBatteryPower(ISteamUtils *steamUtils)
  _THIN_WRAPPER(GetCurrentBatteryPower, "")

uint32 SteamUtils_GetAppID(ISteamUtils *steamUtils)
  _THIN_WRAPPER(GetAppID, "")

void SteamUtils_SetOverlayNotificationPosition(ISteamUtils *steamUtils,
    ENotificationPosition eNotificationPosition)
  _THIN_WRAPPER(SetOverlayNotificationPosition, "%i", eNotificationPosition)

bool SteamUtils_IsAPICallCompleted(ISteamUtils *steamUtils, SteamAPICall_t hSteamAPICall,
    bool *pbFailed)
  _THIN_WRAPPER(IsAPICallCompleted, "%llu,%p", hSteamAPICall, pbFailed)

ESteamAPICallFailure SteamUtils_GetAPICallFailureReason(ISteamUtils *steamUtils,
    SteamAPICall_t hSteamAPICall)
  _THIN_WRAPPER(GetAPICallFailureReason, "%llu", hSteamAPICall)

bool SteamUtils_GetAPICallResult(ISteamUtils *steamUtils, SteamAPICall_t hSteamAPICall,
    void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed)
  _THIN_WRAPPER(GetAPICallResult, "%llu,%p,%i,%i,%p", hSteamAPICall, pCallback, cubCallback,
      iCallbackExpected, pbFailed)

void SteamUtils_RunFrame(ISteamUtils *steamUtils)
  _THIN_WRAPPER(RunFrame, "")

uint32 SteamUtils_GetIPCCallCount(ISteamUtils *steamUtils)
  _THIN_WRAPPER(GetIPCCallCount, "")

// TODO: This just wraps around the seemingly equivalent SteamClient call.  Is that alright?
// TODO: It's probably safe to just pass this pointer directly to steam, FYI
void SteamUtils_SetWarningMessageHook(ISteamUtils *steamUtils,
    SteamAPIWarningMessageHook_t pFunction)
{
  WINE_TRACE("%p,%p", steamUtils, pFunction);
  SteamClient_SetWarningMessageHook(SteamClient_(), pFunction);
}

bool SteamUtils_IsOverlayEnabled(ISteamUtils *steamUtils)
  _THIN_WRAPPER(IsOverlayEnabled, "")

bool SteamUtils_BOverlayNeedsPresent(ISteamUtils *steamUtils)
  _THIN_WRAPPER(BOverlayNeedsPresent, "")

SteamAPICall_t SteamUtils_CheckFileSignature(ISteamUtils *steamUtils, const char *szFileName)
  _THIN_WRAPPER(CheckFileSignature, "\"%s\"", szFileName)

bool SteamUtils_ShowGamepadTextInput(ISteamUtils *steamUtils, EGamepadTextInputMode eInputMode,
    EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32 unCharMax)
  _THIN_WRAPPER(ShowGamepadTextInput, "%i,%i,\"%s\",%u", eInputMode, eLineInputMode,
      pchDescription, unCharMax)

uint32 SteamUtils_GetEnteredGamepadTextLength(ISteamUtils *steamUtils)
  _THIN_WRAPPER(GetEnteredGamepadTextLength, "")

bool SteamUtils_GetEnteredGamepadTextInput(ISteamUtils *steamUtils, char *pchText, uint32 cchText)
  _THIN_WRAPPER(GetEnteredGamepadTextInput, "%p,%u", pchText, cchText)

const char *SteamUtils_GetSteamUILanguage(ISteamUtils *steamUtils)
  _THIN_WRAPPER(GetSteamUILanguage, "")

} // extern "C"

