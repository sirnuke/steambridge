// utils_api.cpp - Utils API & SteamUtilsWrapper

#include "stdafx.h"

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"
#include "utils_api.h"

#include <steam_api_bridge.h>

SteamUtilsWrapper::SteamUtilsWrapper() : steamUtils(NULL)
{
  __TRACE("(this=0x%p)", this);
  steamUtils = steam_bridge_SteamUtils();
  __LOG("Wrapping ISteamUtils (0x%p) into (0x%p)", steamUtils, this);
}

uint32 SteamUtilsWrapper::GetSecondsSinceAppActive()
  __STUB("")

uint32 SteamUtilsWrapper::GetSecondsSinceComputerActive()
  __STUB("")

int SteamUtilsWrapper::GetConnectedUniverse()
  __STUB("")

uint32 SteamUtilsWrapper::GetServerRealTime()
  __STUB("")

const char *SteamUtilsWrapper::GetIPCountry()
  __STUB("")

bool SteamUtilsWrapper::GetImageSize(int iImage, uint32 *pnWidth,
    uint32 *pnHeight)
  __STUB("(%i,0x%p,0x%p)", iImage, pnWidth, pnHeight)

bool SteamUtilsWrapper::GetImageRGBA(int iImage, uint8 *pubDest,
    int nDestBufferSize)
  __STUB("(%i,0x%p,%i)", iImage, pubDest, nDestBufferSize)

bool SteamUtilsWrapper::GetCSERIPPort(uint32 *unIP, uint16 *usPort)
  __STUB("(0x%p,0x%p)", unIP, usPort)

uint8 SteamUtilsWrapper::GetCurrentBatteryPower()
  __STUB("")

uint32 SteamUtilsWrapper::GetAppID()
  __STUB("")

void SteamUtilsWrapper::SetOverlayNotificationPosition(
    int eNotificationPosition)
{
  __TRACE("(%i)", eNotificationPosition);
  steam_bridge_SteamUtils_SetOverlayNotificationPosition(steamUtils,
    eNotificationPosition);
}

bool SteamUtilsWrapper::IsAPICallCompleted(SteamAPICall_t hSteamAPICall,
    bool *pbFailed)
  __STUB("(%llu,0x%p)", hSteamAPICall, pbFailed)

int SteamUtilsWrapper::GetAPICallFailureReason(SteamAPICall_t hSteamAPICall)
  __STUB("(%llu)", hSteamAPICall)

bool SteamUtilsWrapper::GetAPICallResult(SteamAPICall_t hSteamAPICall,
    void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed)
  __STUB("(%llu,0x%p,%i,%i,0x%p)", hSteamAPICall, pCallback, cubCallback,
      iCallbackExpected, pbFailed)

void SteamUtilsWrapper::RunFrame()
  __STUB("")

uint32 SteamUtilsWrapper::GetIPCCallCount()
  __STUB("")

void SteamUtilsWrapper::SetWarningMessageHook(
    SteamAPIWarningMessageHook_t pFunction)
  __STUB("(0x%p)", pFunction)

bool SteamUtilsWrapper::IsOverlayEnabled()
  __STUB("")

bool SteamUtilsWrapper::BOverlayNeedsPresent()
  __STUB("")

SteamAPICall_t SteamUtilsWrapper::CheckFileSignature(const char *szFileName)
  __STUB("(\"%s\")", szFileName)

bool SteamUtilsWrapper::ShowGamepadTextInput(int eInputMode, int eLineInputMode,
    const char *pchDescription, uint32 unCharMax)
  __STUB("(%i,%i,\"%s\",%u)", eInputMode, eLineInputMode, pchDescription,
      unCharMax)

uint32 SteamUtilsWrapper::GetEnteredGamepadTextLength()
  __STUB("")

bool SteamUtilsWrapper::GetEnteredGamepadTextInput(char *pchText, uint32 cchText)
  __STUB("(0x%p,%u)", pchText, cchText)	

const char *SteamUtilsWrapper::GetSteamUILanguage()
  __STUB("")

extern "C"
{

STEAM_API_PROXY_API void *SteamUtils()
{
  __TRACE("()");
  return state.getSteamUtils();
}

} //extern "C"

