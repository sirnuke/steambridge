// utils_api.cpp - Autogenerated source for ISteamUtils
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

SteamUtils::SteamUtils() : steamUtils(NULL)
{
  __TRACE("(this=0x%p)", this);
  steamUtils = SteamUtils_();
  __LOG("Wrapping ISteamUtils (0x%p) into (0x%p)", steamUtils, this);
}

uint32 SteamUtils::GetSecondsSinceAppActive()
{
  __TRACE("()");
  uint32 result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+0]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    add esp, 4
  }
  return result;
}

uint32 SteamUtils::GetSecondsSinceComputerActive()
{
  __TRACE("()");
  uint32 result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+4]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    add esp, 4
  }
  return result;
}

EUniverse SteamUtils::GetConnectedUniverse()
{
  __TRACE("()");
  EUniverse result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+8]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    add esp, 4
  }
  return result;
}

uint32 SteamUtils::GetServerRealTime()
{
  __TRACE("()");
  uint32 result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+12]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    add esp, 4
  }
  return result;
}

const char *SteamUtils::GetIPCountry()
{
  __TRACE("()");
  const char *result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+16]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    add esp, 4
  }
  return result;
}

bool SteamUtils::GetImageSize(int iImage, uint32 *pnWidth, uint32 *pnHeight)
{
  __TRACE("(%i,0x%p,0x%p,)", iImage, pnWidth, pnHeight);
  bool result;
  __asm
  {
    // Push function arguments
    mov eax, pnHeight
    push eax
    // Push function arguments
    mov eax, pnWidth
    push eax
    // Push function arguments
    mov eax, iImage
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+20]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    add esp, 16
  }
  return result;
}

bool SteamUtils::GetImageRGBA(int iImage, uint8 *pubDest, int nDestBufferSize)
{
  __TRACE("(%i,0x%p,%i,)", iImage, pubDest, nDestBufferSize);
  bool result;
  __asm
  {
    // Push function arguments
    mov eax, nDestBufferSize
    push eax
    // Push function arguments
    mov eax, pubDest
    push eax
    // Push function arguments
    mov eax, iImage
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+24]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    add esp, 16
  }
  return result;
}

bool SteamUtils::GetCSERIPPort(uint32 *unIP, uint16 *usPort)
{
  __TRACE("(0x%p,0x%p,)", unIP, usPort);
  bool result;
  __asm
  {
    // Push function arguments
    mov eax, usPort
    push eax
    // Push function arguments
    mov eax, unIP
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+28]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    add esp, 12
  }
  return result;
}

uint8 SteamUtils::GetCurrentBatteryPower()
{
  __TRACE("()");
  uint8 result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+32]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    add esp, 4
  }
  return result;
}

uint32 SteamUtils::GetAppID()
{
  __TRACE("()");
  uint32 result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+36]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    add esp, 4
  }
  return result;
}

void SteamUtils::SetOverlayNotificationPosition(ENotificationPosition eNotificationPosition)
{
  __TRACE("(%i,)", eNotificationPosition);
  __asm
  {
    // Push function arguments
    mov eax, eNotificationPosition
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+40]
    // Call that memory location
    call eax
    // Move the returned value into the result
    // restore stack
    add esp, 8
  }
}

bool SteamUtils::IsAPICallCompleted(SteamAPICall_t hSteamAPICall, bool *pbFailed)
{
  __TRACE("(%llu,0x%p,)", hSteamAPICall, pbFailed);
  bool result;
  __asm
  {
    // Push function arguments
    mov eax, pbFailed
    push eax
    // Push function arguments
    lea edx, hSteamAPICall
    mov eax, [edx+4]
    push eax
    mov eax, [edx+0]
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+44]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    add esp, 16
  }
  return result;
}

ESteamAPICallFailure SteamUtils::GetAPICallFailureReason(SteamAPICall_t hSteamAPICall)
{
  __TRACE("(%llu,)", hSteamAPICall);
  ESteamAPICallFailure result;
  __asm
  {
    // Push function arguments
    lea edx, hSteamAPICall
    mov eax, [edx+4]
    push eax
    mov eax, [edx+0]
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+48]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    add esp, 12
  }
  return result;
}

bool SteamUtils::GetAPICallResult(SteamAPICall_t hSteamAPICall, void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed)
{
  __TRACE("(%llu,0x%p,%i,%i,0x%p,)", hSteamAPICall, pCallback, cubCallback, iCallbackExpected, pbFailed);
  bool result;
  __asm
  {
    // Push function arguments
    mov eax, pbFailed
    push eax
    // Push function arguments
    mov eax, iCallbackExpected
    push eax
    // Push function arguments
    mov eax, cubCallback
    push eax
    // Push function arguments
    mov eax, pCallback
    push eax
    // Push function arguments
    lea edx, hSteamAPICall
    mov eax, [edx+4]
    push eax
    mov eax, [edx+0]
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+52]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    add esp, 28
  }
  return result;
}

void SteamUtils::RunFrame()
{
  __TRACE("()");
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+56]
    // Call that memory location
    call eax
    // Move the returned value into the result
    // restore stack
    add esp, 4
  }
}

uint32 SteamUtils::GetIPCCallCount()
{
  __TRACE("()");
  uint32 result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+60]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    add esp, 4
  }
  return result;
}

void SteamUtils::SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction)
{
  __TRACE("(0x%p,)", pFunction);
  __asm
  {
    // Push function arguments
    mov eax, pFunction
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+64]
    // Call that memory location
    call eax
    // Move the returned value into the result
    // restore stack
    add esp, 8
  }
}

bool SteamUtils::IsOverlayEnabled()
{
  __TRACE("()");
  bool result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+68]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    add esp, 4
  }
  return result;
}

bool SteamUtils::BOverlayNeedsPresent()
{
  __TRACE("()");
  bool result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+72]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    add esp, 4
  }
  return result;
}

SteamAPICall_t SteamUtils::CheckFileSignature(const char *szFileName)
{
  __TRACE("(\"%s\",)", szFileName);
  SteamAPICall_t result;
  __asm
  {
    // Push function arguments
    mov eax, szFileName
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+76]
    // Call that memory location
    call eax
    // Move the returned value into the result
    lea ecx, result
    mov [ecx+0], eax
    mov [ecx+4], edx
    // restore stack
    add esp, 8
  }
  return result;
}

bool SteamUtils::ShowGamepadTextInput(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32 unCharMax)
{
  __TRACE("(%i,%i,\"%s\",%u,)", eInputMode, eLineInputMode, pchDescription, unCharMax);
  bool result;
  __asm
  {
    // Push function arguments
    mov eax, unCharMax
    push eax
    // Push function arguments
    mov eax, pchDescription
    push eax
    // Push function arguments
    mov eax, eLineInputMode
    push eax
    // Push function arguments
    mov eax, eInputMode
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+80]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    add esp, 20
  }
  return result;
}

uint32 SteamUtils::GetEnteredGamepadTextLength()
{
  __TRACE("()");
  uint32 result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+84]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    add esp, 4
  }
  return result;
}

bool SteamUtils::GetEnteredGamepadTextInput(char *pchText, uint32 cchText)
{
  __TRACE("(0x%p,%u,)", pchText, cchText);
  bool result;
  __asm
  {
    // Push function arguments
    mov eax, cchText
    push eax
    // Push function arguments
    mov eax, pchText
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+88]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    add esp, 12
  }
  return result;
}

const char *SteamUtils::GetSteamUILanguage()
{
  __TRACE("()");
  const char *result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamUtils
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+92]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    add esp, 4
  }
  return result;
}

#include "utils_api_code.inc"

