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
  STEAM_API_BRIDGE_API bool steam_bridge_SteamAPI_InitSafe() __STUB__;
  STEAM_API_BRIDGE_API int steam_bridge_SteamAPI_RegisterCallback(steam_bridge_CallbackRunFunc, steam_bridge_CallbackRunArgsFunc, void *, int, int) __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_RunCallbacks() __STUB__;

  STEAM_API_BRIDGE_API class ISteamUser *steam_bridge_SteamUser() __STUB__;
  //STEAM_API_BRIDGE_API uint64 steam_bridge_SteamUser_GetSteamID(class ISteamUser *) __STUB__;
  STEAM_API_BRIDGE_API void *steam_bridge_SteamUser_GetSteamID(class ISteamUser *) __STUB__;
  STEAM_API_BRIDGE_API bool steam_bridge_SteamUser_BLoggedOn(class ISteamUser *steamUser) __STUB__;

  STEAM_API_BRIDGE_API class ISteamFriends *steam_bridge_SteamFriends() __STUB__;
  STEAM_API_BRIDGE_API const char *steam_bridge_SteamFriends_GetPersonaName(class ISteamFriends *) __STUB__;
  STEAM_API_BRIDGE_API int steam_bridge_SteamFriends_GetFriendCount(class ISteamFriends *, int) __STUB__;

  STEAM_API_BRIDGE_API class ISteamApps *steam_bridge_SteamApps() __STUB__;
  STEAM_API_BRIDGE_API bool steam_bridge_SteamApps_BIsSubscribedApp(class ISteamApps *, AppId_t) __STUB__;
  STEAM_API_BRIDGE_API const char *steam_bridge_SteamApps_GetCurrentGameLanguage(class ISteamApps *) __STUB__;

  STEAM_API_BRIDGE_API class ISteamUserStats *steam_bridge_SteamUserStats() __STUB__;
  STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_RequestCurrentStats(class ISteamUserStats *) __STUB__;

  STEAM_API_BRIDGE_API const char *steam_bridge_version_string() __STUB__;
  STEAM_API_BRIDGE_API const char *steam_bridge_info_string() __STUB__;
}
