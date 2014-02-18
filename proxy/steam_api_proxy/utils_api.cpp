// utils_api.cpp - Utils API & SteamUtilsWrapper
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include "stdafx.h"

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"
#include "utils_api.h"

#include <steam_api_bridge.h>

#define _THIN_WRAPPER(API, TRACE, ...) { \
  __TRACE("" TRACE "", ##__VA_ARGS__); \
  return SteamUtils_  ##API(steamUtils, ##__VA_ARGS__); \
}

SteamUtilsWrapper::SteamUtilsWrapper() : steamUtils(NULL)
{
  __TRACE("(this=0x%p)", this);
  steamUtils = SteamUtils_();
  __LOG("Wrapping ISteamUtils (0x%p) into (0x%p)", steamUtils, this);
}

uint32 SteamUtilsWrapper::GetSecondsSinceAppActive()
  _THIN_WRAPPER(GetSecondsSinceAppActive, "")

uint32 SteamUtilsWrapper::GetSecondsSinceComputerActive()
  _THIN_WRAPPER(GetSecondsSinceComputerActive, "")

int SteamUtilsWrapper::GetConnectedUniverse()
  _THIN_WRAPPER(GetConnectedUniverse, "")

uint32 SteamUtilsWrapper::GetServerRealTime()
  _THIN_WRAPPER(GetServerRealTime, "")

const char *SteamUtilsWrapper::GetIPCountry()
  _THIN_WRAPPER(GetIPCountry, "")

bool SteamUtilsWrapper::GetImageSize(int iImage, uint32 *pnWidth,
    uint32 *pnHeight)
  _THIN_WRAPPER(GetImageSize, "%i,0x%p,0x%p", iImage, pnWidth, pnHeight)

bool SteamUtilsWrapper::GetImageRGBA(int iImage, uint8 *pubDest,
    int nDestBufferSize)
  _THIN_WRAPPER(GetImageRGBA, "%i,0x%p,%i", iImage, pubDest, nDestBufferSize)

bool SteamUtilsWrapper::GetCSERIPPort(uint32 *unIP, uint16 *usPort)
  _THIN_WRAPPER(GetCSERIPPort, "0x%p,0x%p", unIP, usPort)

uint8 SteamUtilsWrapper::GetCurrentBatteryPower()
  _THIN_WRAPPER(GetCurrentBatteryPower, "")

uint32 SteamUtilsWrapper::GetAppID()
  _THIN_WRAPPER(GetAppID, "")

void SteamUtilsWrapper::SetOverlayNotificationPosition(
    int eNotificationPosition)
  _THIN_WRAPPER(SetOverlayNotificationPosition, "%i", eNotificationPosition)

bool SteamUtilsWrapper::IsAPICallCompleted(SteamAPICall_t hSteamAPICall,
    bool *pbFailed)
  _THIN_WRAPPER(IsAPICallCompleted, "%llu,0x%p", hSteamAPICall, pbFailed)

int SteamUtilsWrapper::GetAPICallFailureReason(SteamAPICall_t hSteamAPICall)
  _THIN_WRAPPER(GetAPICallFailureReason, "%llu", hSteamAPICall)

bool SteamUtilsWrapper::GetAPICallResult(SteamAPICall_t hSteamAPICall,
    void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed)
  _THIN_WRAPPER(GetAPICallResult, "%llu,0x%p,%i,%i,0x%p", hSteamAPICall, pCallback, cubCallback,
      iCallbackExpected, pbFailed)

void SteamUtilsWrapper::RunFrame()
  _THIN_WRAPPER(RunFrame, "")

uint32 SteamUtilsWrapper::GetIPCCallCount()
  _THIN_WRAPPER(GetIPCCallCount, "")

void SteamUtilsWrapper::SetWarningMessageHook(
    SteamAPIWarningMessageHook_t pFunction)
  _THIN_WRAPPER(SetWarningMessageHook, "0x%p", pFunction)

bool SteamUtilsWrapper::IsOverlayEnabled()
  _THIN_WRAPPER(IsOverlayEnabled, "")

bool SteamUtilsWrapper::BOverlayNeedsPresent()
  _THIN_WRAPPER(BOverlayNeedsPresent, "")

SteamAPICall_t SteamUtilsWrapper::CheckFileSignature(const char *szFileName)
  _THIN_WRAPPER(CheckFileSignature, "\"%s\"", szFileName)

bool SteamUtilsWrapper::ShowGamepadTextInput(int eInputMode, int eLineInputMode,
    const char *pchDescription, uint32 unCharMax)
  _THIN_WRAPPER(ShowGamepadTextInput, "%i,%i,\"%s\",%u", eInputMode, eLineInputMode, pchDescription,
      unCharMax)

uint32 SteamUtilsWrapper::GetEnteredGamepadTextLength()
  _THIN_WRAPPER(GetEnteredGamepadTextLength, "")

bool SteamUtilsWrapper::GetEnteredGamepadTextInput(char *pchText, uint32 cchText)
  _THIN_WRAPPER(GetEnteredGamepadTextInput, "0x%p,%u", pchText, cchText)	

const char *SteamUtilsWrapper::GetSteamUILanguage()
  _THIN_WRAPPER(GetSteamUILanguage, "")

extern "C"
{

STEAM_API_PROXY_API void *SteamUtils()
{
  __TRACE("");
  return state.getSteamUtils();
}

} //extern "C"

