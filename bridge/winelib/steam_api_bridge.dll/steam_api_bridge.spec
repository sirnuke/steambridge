# steam_api_bridge Winelib spec file

# Core API calls
@ cdecl steam_bridge_SteamAPI_InitSafe()
@ cdecl steam_bridge_SteamAPI_Shutdown()
@ cdecl steam_bridge_SteamAPI_RegisterCallback(ptr ptr ptr long long)
@ cdecl steam_bridge_SteamAPI_UnregisterCallback(ptr)
@ cdecl steam_bridge_SteamAPI_RunCallbacks();

# SteamClient API Calls
@ cdecl steam_bridge_SteamClient()
@ cdecl steam_bridge_SteamClient_SetWarningMessageHook(ptr)

# SteamUser API calls
@ cdecl steam_bridge_SteamUser(str)
@ cdecl steam_bridge_SteamUser_GetSteamID(ptr ptr)
@ cdecl steam_bridge_SteamUser_BLoggedOn(ptr)
#@ cdecl steam_bridge_SteamUser_InitiateGameConnection(ptr ptr long int64 long word long)
# TODO: Second to last parameter is an unsigned short (16-bits) -
#       Winelib documenation suggests this is still a 'long'
@ cdecl steam_bridge_SteamUser_InitiateGameConnection(ptr ptr long int64 long long long)
#@ cdecl steam_bridge_SteamUser_TerminateGameConnection(ptr long word)
@ cdecl steam_bridge_SteamUser_TerminateGameConnection(ptr long long)

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

# SteamUtils API Calls
@ cdecl steam_bridge_SteamUtils()

# Meta API calls
@ cdecl steam_bridge_version_string()
@ cdecl steam_bridge_info_string()
