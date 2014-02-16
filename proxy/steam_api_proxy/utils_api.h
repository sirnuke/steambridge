// utils_api.h - Utils API & SteamUtilsWrapper
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#pragma once

#include <string>

#include "types.h"

class ISteamUtils;

class SteamUtilsWrapper
{
  public:
    virtual uint32 GetSecondsSinceAppActive();
    virtual uint32 GetSecondsSinceComputerActive();

    // EUniverse ... ()
    virtual int GetConnectedUniverse();

    virtual uint32 GetServerRealTime();

    virtual const char *GetIPCountry();

    virtual bool GetImageSize(int iImage, uint32 *pnWidth, uint32 *pnHeight);

    virtual bool GetImageRGBA(int iImage, uint8 *pubDest, int nDestBufferSize);

    virtual bool GetCSERIPPort(uint32 *unIP, uint16 *usPort);

    virtual uint8 GetCurrentBatteryPower();

    virtual uint32 GetAppID();

    // void ... (ENotificationPosition)
    virtual void SetOverlayNotificationPosition(int eNotificationPosition);

    virtual bool IsAPICallCompleted(SteamAPICall_t hSteamAPICall, bool *pbFailed);
    // ESteamAPICallFailure ... (SteamAPICall_t)
    virtual int GetAPICallFailureReason(SteamAPICall_t hSteamAPICall);
    virtual bool GetAPICallResult(SteamAPICall_t hSteamAPICall,
        void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed);

    virtual void RunFrame();

    virtual uint32 GetIPCCallCount();

    virtual void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction);

    virtual bool IsOverlayEnabled();

    virtual bool BOverlayNeedsPresent();

    virtual SteamAPICall_t CheckFileSignature(const char *szFileName);

    // bool ... (EGamepadTextInputMode, EGamepadTextInputLineMode,
    //           const char *, uint32)
    virtual bool ShowGamepadTextInput(int eInputMode, int eLineInputMode,
        const char *pchDescription, uint32 unCharMax);

    virtual uint32 GetEnteredGamepadTextLength();
    virtual bool GetEnteredGamepadTextInput(char *pchText, uint32 cchText);	

    virtual const char *GetSteamUILanguage();

    SteamUtilsWrapper();

  private:
    ISteamUtils *steamUtils;
};

