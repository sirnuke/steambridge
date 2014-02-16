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
@ cdecl steam_bridge_SteamFriends_SetPlayedWith(ptr int64)

# SteamApps API Calls
@ cdecl steam_bridge_SteamApps()
@ cdecl steam_bridge_SteamApps_BIsSubscribedApp(ptr long)
@ cdecl steam_bridge_SteamApps_GetCurrentGameLanguage()

# SteamUserStats API Calls
@ cdecl steam_bridge_SteamUserStats()
@ cdecl steam_bridge_SteamUserStats_RequestCurrentStats(ptr)
@ cdecl steam_bridge_SteamUserStats_GetStatI(ptr str ptr)
@ cdecl steam_bridge_SteamUserStats_GetStatF(ptr str ptr)
@ cdecl steam_bridge_SteamUserStats_SetStatI(ptr str long)
@ cdecl steam_bridge_SteamUserStats_SetStatF(ptr str float)
@ cdecl steam_bridge_SteamUserStats_UpdateAvgRateStat(ptr str float double)
@ cdecl steam_bridge_SteamUserStats_GetAchievement(ptr str ptr)
@ cdecl steam_bridge_SteamUserStats_SetAchievement(ptr str)
@ cdecl steam_bridge_SteamUserStats_ClearAchievement(ptr str)
@ cdecl steam_bridge_SteamUserStats_GetNumAchievements(ptr)

# SteamUtils API Calls
@ cdecl steam_bridge_SteamUtils()
@ cdecl steam_bridge_SteamUtils_SetOverlayNotificationPosition(ptr long)

# Meta API calls
@ cdecl steam_bridge_version_string()
@ cdecl steam_bridge_info_string()
