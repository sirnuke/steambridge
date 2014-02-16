# steam_api_bridge Winelib spec file

# Core API calls
@ cdecl SteamAPI_InitSafe_()
@ cdecl SteamAPI_Shutdown_()
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
@ cdecl SteamUserStats_()
@ cdecl SteamUserStats_RequestCurrentStats(ptr)
@ cdecl SteamUserStats_GetStatI(ptr str ptr)
@ cdecl SteamUserStats_GetStatF(ptr str ptr)
@ cdecl SteamUserStats_SetStatI(ptr str long)
@ cdecl SteamUserStats_SetStatF(ptr str float)
@ cdecl SteamUserStats_UpdateAvgRateStat(ptr str float double)
@ cdecl SteamUserStats_GetAchievement(ptr str ptr)
@ cdecl SteamUserStats_SetAchievement(ptr str)
@ cdecl SteamUserStats_ClearAchievement(ptr str)
@ cdecl SteamUserStats_GetAchievementAndUnlockTime(ptr str ptr ptr)
@ cdecl SteamUserStats_StoreStats(ptr)
@ cdecl SteamUserStats_GetAchievementIcon(ptr str)
@ cdecl SteamUserStats_GetAchievementDisplayAttribute(ptr str str)
@ cdecl SteamUserStats_GetNumAchievements(ptr)
@ cdecl SteamUserStats_GetAchievementName(ptr long)
@ cdecl SteamUserStats_RequestUserStats(ptr int64)
@ cdecl SteamUserStats_GetUserStatI(ptr int64 str ptr)
@ cdecl SteamUserStats_GetUserStatF(ptr int64 str ptr)
@ cdecl SteamUserStats_GetUserAchievement(ptr int64 str ptr)
@ cdecl SteamUserStats_GetUserAchievementAndUnlockTime(ptr int64 str ptr ptr)
@ cdecl SteamUserStats_ResetAllStats(ptr long)

# SteamUtils API Calls
@ cdecl steam_bridge_SteamUtils()
@ cdecl steam_bridge_SteamUtils_SetOverlayNotificationPosition(ptr long)

# Meta API calls
@ cdecl steam_bridge_version_string()
@ cdecl steam_bridge_info_string()
