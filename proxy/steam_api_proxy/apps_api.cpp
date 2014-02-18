// apps_api.cpp - Autogenerated source for ISteamApps
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include "stdafx.h"

#include "logging.h"
#include "state.h"
#include "steam_api_proxy.h"
#include "types.h"

#include "apps_api.h"

#include <steam_api_bridge.h>

SteamApps::SteamApps() : steamApps(NULL)
{
  __TRACE("(this=0x%p)", this);
  steamApps = SteamApps_();
  __LOG("Wrapping ISteamApps (0x%p) into (0x%p)", steamApps, this);
}

bool SteamApps::BIsSubscribed()
{
  __TRACE("()");
  bool result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+0]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    // including this pointer
    pop eax
  }
  return result;
}

bool SteamApps::BIsLowViolence()
{
  __TRACE("()");
  bool result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+4]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    // including this pointer
    pop eax
  }
  return result;
}

bool SteamApps::BIsCybercafe()
{
  __TRACE("()");
  bool result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+8]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    // including this pointer
    pop eax
  }
  return result;
}

bool SteamApps::BIsVACBanned()
{
  __TRACE("()");
  bool result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+12]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    // including this pointer
    pop eax
  }
  return result;
}

const char *SteamApps::GetCurrentGameLanguage()
{
  __TRACE("()");
  char *result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
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
    // including this pointer
    pop eax
  }
  return result;
}

const char *SteamApps::GetAvailableGameLanguages()
{
  __TRACE("()");
  char *result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+20]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    // including this pointer
    pop eax
  }
  return result;
}

bool SteamApps::BIsSubscribedApp(AppId_t appID)
{
  __TRACE("(%u,)", appID);
  bool result;
  __asm
  {
    // Push function arguments
    mov eax, appID
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
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
    // including this pointer
    pop eax
    pop eax
  }
  return result;
}

bool SteamApps::BIsDlcInstalled(AppId_t appID)
{
  __TRACE("(%u,)", appID);
  bool result;
  __asm
  {
    // Push function arguments
    mov eax, appID
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
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
    // including this pointer
    pop eax
    pop eax
  }
  return result;
}

uint32 SteamApps::GetEarliestPurchaseUnixTime(AppId_t nAppID)
{
  __TRACE("(%u,)", nAppID);
  uint32 result;
  __asm
  {
    // Push function arguments
    mov eax, nAppID
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+32]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    // including this pointer
    pop eax
    pop eax
  }
  return result;
}

bool SteamApps::BIsSubscribedFromFreeWeekend()
{
  __TRACE("()");
  bool result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+36]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    // including this pointer
    pop eax
  }
  return result;
}

int SteamApps::GetDLCCount()
{
  __TRACE("()");
  int result;
  __asm
  {
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+40]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    // including this pointer
    pop eax
  }
  return result;
}

bool SteamApps::BGetDLCDataByIndex(int iDLC, AppId_t *pAppID, bool *pbAvailable, char *pchName, int cchNameBufferSize)
{
  __TRACE("(%i,0x%p,0x%p,0x%p,%i,)", iDLC, pAppID, pbAvailable, pchName, cchNameBufferSize);
  bool result;
  __asm
  {
    // Push function arguments
    mov eax, cchNameBufferSize
    push eax
    // Push function arguments
    mov eax, pchName
    push eax
    // Push function arguments
    mov eax, pbAvailable
    push eax
    // Push function arguments
    mov eax, pAppID
    push eax
    // Push function arguments
    mov eax, iDLC
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
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
    // including this pointer
    pop eax
    pop eax
    pop eax
    pop eax
    pop eax
    pop eax
  }
  return result;
}

void SteamApps::InstallDLC(AppId_t nAppID)
{
  __TRACE("(%u,)", nAppID);
  __asm
  {
    // Push function arguments
    mov eax, nAppID
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+48]
    // Call that memory location
    call eax
    // Move the returned value into the result
    // restore stack
    // including this pointer
    pop eax
    pop eax
  }
}

void SteamApps::UninstallDLC(AppId_t nAppID)
{
  __TRACE("(%u,)", nAppID);
  __asm
  {
    // Push function arguments
    mov eax, nAppID
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+52]
    // Call that memory location
    call eax
    // Move the returned value into the result
    // restore stack
    // including this pointer
    pop eax
    pop eax
  }
}

void SteamApps::RequestAppProofOfPurchaseKey(AppId_t nAppID)
{
  __TRACE("(%u,)", nAppID);
  __asm
  {
    // Push function arguments
    mov eax, nAppID
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+56]
    // Call that memory location
    call eax
    // Move the returned value into the result
    // restore stack
    // including this pointer
    pop eax
    pop eax
  }
}

bool SteamApps::GetCurrentBetaName(char *pchName, int cchNameBufferSize)
{
  __TRACE("(0x%p,%i,)", pchName, cchNameBufferSize);
  bool result;
  __asm
  {
    // Push function arguments
    mov eax, cchNameBufferSize
    push eax
    // Push function arguments
    mov eax, pchName
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+60]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    // including this pointer
    pop eax
    pop eax
    pop eax
  }
  return result;
}

bool SteamApps::MarkContentCorrupt(bool bMissingFilesOnly)
{
  __TRACE("(%i,)", bMissingFilesOnly);
  bool result;
  __asm
  {
    // Push function arguments
    mov al, bMissingFilesOnly
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+64]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // restore stack
    // including this pointer
    pop eax
    pop eax
  }
  return result;
}

uint32 SteamApps::GetInstalledDepots(DepotId_t *pvecDepots, uint32 cMaxDepots)
{
  __TRACE("(0x%p,%u,)", pvecDepots, cMaxDepots);
  uint32 result;
  __asm
  {
    // Push function arguments
    mov eax, cMaxDepots
    push eax
    // Push function arguments
    mov eax, pvecDepots
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+68]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    // including this pointer
    pop eax
    pop eax
    pop eax
  }
  return result;
}

uint32 SteamApps::GetAppInstallDir(AppId_t appID, char *pchFolder, uint32 cchFolderBufferSize)
{
  __TRACE("(%u,0x%p,%u,)", appID, pchFolder, cchFolderBufferSize);
  uint32 result;
  __asm
  {
    // Push function arguments
    mov eax, cchFolderBufferSize
    push eax
    // Push function arguments
    mov eax, pchFolder
    push eax
    // Push function arguments
    mov eax, appID
    push eax
    // Push Linux-side 'this'
    mov eax, [this]
    mov eax, [eax]this.steamApps
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+72]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // restore stack
    // including this pointer
    pop eax
    pop eax
    pop eax
    pop eax
  }
  return result;
}

#include "apps_api_code.inc"

