#!/bin/sh
echo "TODO: Link against the actual libsteam_api.so!"
winemaker steam_api_bridge.dll --nosource-fix --dll --nomfc --wine32 -Iinclude -I/opt/wine-git/include 
