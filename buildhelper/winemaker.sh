#!/bin/sh
LIBRARIES="-ldl"
INCLUDEPATH="-I../../common/steam/ -I../../common/include/"
LIBRARYPATH=""
DEFINES="-DVERSION_SAFE_STEAM_API_INTERFACES"
cd libraries/bridge
winemaker steam_api_bridge.dll --nosource-fix --dll --nomfc --wine32 $DEFINES $INCLUDEPATH $LIBRARYPATH $LIBRARIES
# There HAS to be a better way to do this
sed -i 's/-m32/-m32 -Wall -Wextra -pipe -g/g' steam_api_bridge.dll/Makefile
