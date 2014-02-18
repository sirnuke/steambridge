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

class ISteamClient;
class ISteamUser;
class ISteamFriends;
class ISteamApps;
class ISteamUserStats;
class ISteamUtils;

extern "C" {

// Core API Calls
STEAM_API_BRIDGE_API bool SteamAPI_InitSafe_();
STEAM_API_BRIDGE_API void SteamAPI_Shutdown_();
// TODO: Handle callback flags better, probably don't need/want to
//       return an int here.
STEAM_API_BRIDGE_API int SteamAPI_RegisterCallback_(steam_bridge_CallbackRunFunc, steam_bridge_CallbackRunArgsFunc, void *, int, int);
STEAM_API_BRIDGE_API void SteamAPI_UnregisterCallback_(void *);
STEAM_API_BRIDGE_API void SteamAPI_RunCallbacks_();

// Get ISteam* API Calls
STEAM_API_BRIDGE_API ISteamClient *SteamClient_();
STEAM_API_BRIDGE_API ISteamUser *SteamUser_();
STEAM_API_BRIDGE_API ISteamApps *SteamApps_();
STEAM_API_BRIDGE_API ISteamUserStats *SteamUserStats_();
STEAM_API_BRIDGE_API ISteamUtils *SteamUtils_();

// Meta API Calls
STEAM_API_BRIDGE_API const char *steambridge_version_string();
STEAM_API_BRIDGE_API const char *steambridge_info_string();

} // extern "C"

#endif //___STEAM_API_BRIDGE_API_H___
