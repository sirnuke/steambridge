// api.h - Defines the public API (at least the relevant part)
//
// !!!!!!!!!
// CRITICAL: This file is shared with the win32 Visual Studio project
//           and the Linux Winelib.  Any changes here must be compatable with both
//           Linux and Windows, and changes must update both projects.
// !!!!!!!!!


#ifndef  ___STEAM_API_BRIDGE_API_H___
#define  ___STEAM_API_BRIDGE_API_H___

// TODO: There might be a better way to handle this
#ifndef  STEAM_API_BRIDGE_API 
#define  STEAM_API_BRIDGE_API 
#endif //STEAM_API_BRIDGE_API 

extern "C"
{

STEAM_API_BRIDGE_API bool steam_bridge_SteamAPI_InitSafe(int appid);
STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_RegisterCallback(
    void *wrapper, int callback, int size);

// SteamUser API calls
STEAM_API_BRIDGE_API class ISteamUser *steam_bridge_SteamUser();
STEAM_API_BRIDGE_API uint64 steam_bridge_SteamUser_GetSteamID(
    class ISteamUser *steamUser);
STEAM_API_BRIDGE_API bool steam_bridge_SteamUser_BLoggedOn(
    class ISteamUser *steamUser);

// SteamFriends API calls
STEAM_API_BRIDGE_API class ISteamFriends *steam_bridge_SteamFriends();
STEAM_API_BRIDGE_API const char *steam_bridge_SteamFriends_GetPersonaName(
    class ISteamFriends *steamFriends);
STEAM_API_BRIDGE_API int steam_bridge_SteamFriends_GetFriendCount(
    class ISteamFriends *steamFriends, int iFriendFlags);

// SteamApps API Calls
STEAM_API_BRIDGE_API class ISteamApps *steam_bridge_SteamApps();
STEAM_API_BRIDGE_API bool steam_bridge_SteamApps_BIsSubscribedApp(
    class ISteamApps *steamApps, AppId_t appId);
STEAM_API_BRIDGE_API const char *steam_bridge_SteamApps_GetCurrentGameLanguage(
    class ISteamApps *steamApps);

// SteamUserStats API Calls
STEAM_API_BRIDGE_API class ISteamUserStats *steam_bridge_SteamUserStats();
STEAM_API_BRIDGE_API bool steam_bridge_SteamUserStats_RequestCurrentStats(
    class ISteamUserStats *steamUserStats);

} // extern "C"

#endif //___STEAM_API_BRIDGE_API_H___
