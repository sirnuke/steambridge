#!/bin/sh
winemaker steam_api_bridge.dll --nosource-fix --dll --nomfc --wine32 -Iinclude -I/opt/wine-git/include -I../../../steam/ -L../../../steam -lsteam_api -DVERSION_SAFE_STEAM_API_INTERFACES
