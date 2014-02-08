#!/bin/sh
winemaker steam_api_bridge.dll --nosource-fix --dll --nomfc --wine32 -Iinclude -I../../../common/include -I../../../steam/ -L../../../steam -lsteam_api -DVERSION_SAFE_STEAM_API_INTERFACES -lconfig
