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

STEAM_API_BRIDGE_API void steam_bridge_SteamAPI_RegisterCallback(void *wrapper, int callback, int size);

STEAM_API_BRIDGE_API class ISteamUser *steam_bridge_SteamUser();

//STEAM_API_BRIDGE_API 
} // extern "C"

#endif //___STEAM_API_BRIDGE_API_H___
