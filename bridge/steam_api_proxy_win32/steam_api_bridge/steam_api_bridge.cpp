// steam_api_bridge.cpp - Stub's the public bridge API
//

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
  STEAM_API_BRIDGE_API bool steam_bridge_SteamAPI_InitSafe() __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_Shutdown() __STUB__;
  STEAM_API_BRIDGE_API int steam_bridge_SteamAPI_RegisterCallback(steam_bridge_CallbackRunFunc, steam_bridge_CallbackRunArgsFunc, void *, int, int) __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_UnregisterCallback(void *) __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_RunCallbacks() __STUB__;

  STEAM_API_BRIDGE_API ISteamClient *steam_bridge_SteamClient() __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamClient_SetWarningMessageHook(ISteamClient *, SteamAPIWarningMessageHook_t) __STUB__;

  STEAM_API_BRIDGE_API ISteamUser *steam_bridge_SteamUser() __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamUser_GetSteamID(ISteamUser *, CSteamID *) __STUB__;
  STEAM_API_BRIDGE_API bool steam_bridge_SteamUser_BLoggedOn(ISteamUser *) __STUB__;
  STEAM_API_BRIDGE_API int steam_bridge_SteamUser_InitiateGameConnection(ISteamUser *, void *, int, CSteamID, uint32, uint16, bool) __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamUser_TerminateGameConnection(ISteamUser *, uint32, uint16) __STUB__;

  STEAM_API_BRIDGE_API ISteamFriends *steam_bridge_SteamFriends() __STUB__;
  STEAM_API_BRIDGE_API const char *steam_bridge_SteamFriends_GetPersonaName(ISteamFriends *) __STUB__;
  STEAM_API_BRIDGE_API int steam_bridge_SteamFriends_GetFriendCount(ISteamFriends *, int) __STUB__;

  STEAM_API_BRIDGE_API ISteamApps *steam_bridge_SteamApps() __STUB__;
  STEAM_API_BRIDGE_API bool steam_bridge_SteamApps_BIsSubscribedApp(ISteamApps *, AppId_t) __STUB__;
  STEAM_API_BRIDGE_API const char *steam_bridge_SteamApps_GetCurrentGameLanguage(ISteamApps *) __STUB__;

  STEAM_API_BRIDGE_API ISteamUserStats *steam_bridge_SteamUserStats() __STUB__;
  STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_RequestCurrentStats(ISteamUserStats *) __STUB__;
  STEAM_API_BRIDGE_API uint32 steam_bridge_SteamUserStats_GetNumAchievements(ISteamUserStats *) __STUB__;

  STEAM_API_BRIDGE_API ISteamUtils *steam_bridge_SteamUtils() __STUB__;
  STEAM_API_BRIDGE_API void steam_bridge_SteamUtils_SetOverlayNotificationPosition(ISteamUtils *, int) __STUB__;

  STEAM_API_BRIDGE_API const char *steam_bridge_version_string() __STUB__;
  STEAM_API_BRIDGE_API const char *steam_bridge_info_string() __STUB__;
}
