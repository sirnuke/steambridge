// steam_api_bridge.cpp - Stub's the public bridge API
//

#include "stdafx.h"

#include <cstdlib>

#include "steam_api_bridge.h"

#define __STUB__ { __stub__(); }
 __declspec(noreturn) void __stub__()
 {
   exit(1);
 }

extern "C"
{
  STEAM_API_BRIDGE_API bool steam_bridge_SteamAPI_InitSafe(int appid) __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_RegisterCallback(void *, int, int) __STUB__;
  STEAM_API_BRIDGE_API class ISteamUser *steam_bridge_SteamUser() __STUB__;
  STEAM_API_BRIDGE_API uint64 steam_bridge_SteamUser_GetSteamID(class ISteamUser *) __STUB__;
}
