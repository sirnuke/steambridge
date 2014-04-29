# steam_api_bridge Winelib spec file

# Core API calls
@ cdecl SteamAPI_InitSafe_()
@ cdecl SteamAPI_Shutdown_()
@ cdecl SteamAPI_RegisterCallback_(ptr ptr ptr long long)
@ cdecl SteamAPI_UnregisterCallback_(ptr)
@ cdecl SteamAPI_RunCallbacks_()

# Get ISteam* API Calls
@ cdecl SteamClient_()
@ cdecl SteamUser_()
@ cdecl SteamFriends_()
@ cdecl SteamApps_()
@ cdecl SteamUserStats_()
@ cdecl SteamUtils_()

# Meta API calls
@ cdecl steambridge_version_string()
@ cdecl steambridge_info_string()

