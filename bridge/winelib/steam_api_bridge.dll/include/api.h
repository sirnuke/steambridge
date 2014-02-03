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

// Callback function pointer types
// See documentation in callback.cpp for more information about this
typedef void (*steam_bridge_CallbackRunFunc)(void *wrapper, int flags,
    void *data);
typedef void (*steam_bridge_CallbackRunArgsFunc)(void *wrapper, int flags,
    void *data, bool ioFailure, SteamAPICall_t steamAPICall);

extern "C"
{

// Core API Calls
STEAM_API_BRIDGE_API bool steam_bridge_SteamAPI_InitSafe();
STEAM_API_BRIDGE_API int steam_bridge_SteamAPI_RegisterCallback(
    steam_bridge_CallbackRunFunc run, steam_bridge_CallbackRunArgsFunc runargs,
    void *wrapper, int callback, int size);
STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_RunCallbacks();

// SteamUser API calls
STEAM_API_BRIDGE_API class ISteamUser *steam_bridge_SteamUser();

// TODO: This returns a 'CSteamID', which is a set 64-bits.
//       It's relatively cleanly converted between uint64 and the struct,
//       BUT depending on the API definition, how they are returned
//       changes.  32-bit ints are returned as EAX (easy), 64-bit ints
//       are returned as EAX+EDX (harder), and struct use some black magic
//       that may or may not be correctly supported by winelib as of
//       this comment.  At a quick glance, this is the only function
//       that returns a struct in this mannor, and it may be easier to
//       just return a uint64 and do a quick convert win32 side.

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

// Meta API Calls
STEAM_API_BRIDGE_API const char *steam_bridge_version_string();
STEAM_API_BRIDGE_API const char *steam_bridge_info_string();

} // extern "C"

#endif //___STEAM_API_BRIDGE_API_H___
