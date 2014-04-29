// steam_api_bridge.cpp - Stub's the public bridge API
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include "stdafx.h"

#include <cstdlib>

#include <types.h>

#include "steam_api_bridge.h"

#define __STUB__ { __stub__(); }
 __declspec(noreturn) void __stub__()
 {
   exit(1);
 }

extern "C"
{
  STEAM_API_BRIDGE_API bool SteamAPI_InitSafe_() __STUB__;
  STEAM_API_BRIDGE_API void SteamAPI_Shutdown_() __STUB__;
  STEAM_API_BRIDGE_API int SteamAPI_RegisterCallback_(steam_bridge_CallbackRunFunc, steam_bridge_CallbackRunArgsFunc, void *, int, int) __STUB__;
  STEAM_API_BRIDGE_API void SteamAPI_UnregisterCallback_(void *) __STUB__;
  STEAM_API_BRIDGE_API void SteamAPI_RunCallbacks_() __STUB__;

  STEAM_API_BRIDGE_API ISteamClient *SteamClient_() __STUB__;
  STEAM_API_BRIDGE_API ISteamUser *SteamUser_() __STUB__;
  STEAM_API_BRIDGE_API ISteamFriends *SteamFriends_() __STUB__;
  STEAM_API_BRIDGE_API ISteamApps *SteamApps_() __STUB__;
  STEAM_API_BRIDGE_API ISteamUserStats *SteamUserStats_() __STUB__;
  STEAM_API_BRIDGE_API ISteamUtils *SteamUtils_() __STUB__;

  STEAM_API_BRIDGE_API const char *steambridge_version_string() __STUB__;
  STEAM_API_BRIDGE_API const char *steambridge_info_string() __STUB__;
}
