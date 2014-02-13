# filesystem.py - Stores various code related to the deployed filesystem

import os

# Root directory of the Steam installation
STEAM_ROOT = os.path.expanduser("~") + "/.steam/root"

# Root directory of the SteamBridge deployment
STEAM_BRIDGE_ROOT = STEAM_ROOT + "/SteamBridge"

# Location of the Win32 native steam_api proxy DLL
PROXY_DLL = STEAM_BRIDGE_ROOT + "/steam_api_proxy.dll"

# Location of the Winelib bridge library
BRIDGE_LIB = STEAM_BRIDGE_ROOT + "/steam_api_bridge.dll.so"

# Location of the native Linux steam_api library
STEAM_API_LIB = STEAM_BRIDGE_ROOT + "/libsteam_api.so"

# The root directory of the internal AppDB
APPDB_ROOT = STEAM_ROOT + "/appdb"

