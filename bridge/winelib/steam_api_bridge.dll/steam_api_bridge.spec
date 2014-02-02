# steam_api_bridge Winelib spec file

# Core API calls
@ cdecl steam_bridge_SteamAPI_InitSafe()
@ cdecl steam_bridge_SteamAPI_RegisterCallback(ptr ptr ptr long long)
@ cdecl steam_bridge_SteamAPI_RunCallbacks();

# SteamUser API calls
@ cdecl steam_bridge_SteamUser(str)
#@ cdecl -ret64 -arch=i386 steam_bridge_SteamUser_GetSteamID(ptr)
@ cdecl steam_bridge_SteamUser_GetSteamID(ptr)
@ cdecl steam_bridge_SteamUser_BLoggedOn(ptr)

# SteamFriends API Calls
@ cdecl steam_bridge_SteamFriends()
@ cdecl steam_bridge_SteamFriends_GetPersonaName(ptr)
@ cdecl steam_bridge_SteamFriends_GetFriendCount(ptr long)

# SteamApps API Calls
@ cdecl steam_bridge_SteamApps()
@ cdecl steam_bridge_SteamApps_BIsSubscribedApp(ptr long)
@ cdecl steam_bridge_SteamApps_GetCurrentGameLanguage()

# SteamUserStats API Calls
@ cdecl steam_bridge_SteamUserStats()
@ cdecl steam_bridge_SteamUserStats_RequestCurrentStats(ptr)

# Meta API calls
@ cdecl steam_bridge_version_string()
@ cdecl steam_bridge_info_string()
