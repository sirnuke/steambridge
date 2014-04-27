#!/bin/bash
#
# Defines various constants used in the entirety of shell scripting.
# To override any values, copy this file to common/local.sh and modify
# as you see fit.

# Root directory of the local steam installation
# (this is hardcoded to be home directory+$STEAM_ROOT)
STEAM_ROOT=/.steam/root

# Location of appmanifest_*.acf files
STEAM_APPMANIFESTS=$STEAM_ROOT/SteamApps

# Common root of installed Steam games
STEAM_APPS=$STEAM_ROOT/SteamApps/common

# Root directory of the user's SteamBridge files
STEAM_BRIDGE_ROOT=$STEAM_ROOT/SteamBridge

# Configuration filename, used by the C++ library
CONFIG_FILENAME=$STEAM_BRIDGE_ROOT/config.json

# Root directory of the internal AppDB
APPDB_ROOT=$STEAM_BRIDGE_ROOT/appdb

# AppDB configuration filename
APPDB_CONFIG=appdb.json

# Default prefix install directory
PREFIX=/usr/lib/local

# Shared files directory
SHARE=$PREFIX/share/steambridge

# Location of Winelib DLLs, used as WINEDLLPATH
WINELIB_PATH=$SHARED
#
# Location of the Winelib bridge library
BRIDGE_LIB=$SHARED/steam_api_bridge.dll.so

# Location of the native Linux steam_api library
STEAM_API_LIB=$SHARED/libsteam_api.so

# Location of the Win32 native steam_api proxy DLL
PROXY_DLL=$SHARED/steam_api_proxy.dll

# Directory storing the SteamBridge tools
TOOLS_DIR=$PREFIX/bin

# Directory storing the Python support module 
PYRUNTIME_DIR=$SHARE/pysteambridge

if [ -f common/local.sh ]; then
  . ./common/local.sh
fi

# Don't modify any of these inside common/local.sh, as they are
# overwritten.

APP_NAME=SteamBridge
WEBPAGE=https://github.com/sirnuke/steambridge/

# Base version string
VERSION_MAJOR=0
VERSION_MINOR=0
VERSION_PATCH=2

# Bit of data about the build
GIT_HEAD=`git rev-parse HEAD`
CONFIG_TIME=`date`

VERSION_SHORT="$VERSION_MAJOR.$VERSION_MINOR.$VERSION_PATCH"
VERSION_LONG="$VERSION_MAJOR.$VERSION_MINOR.$VERSION_PATCH (git-head:$GIT_HEAD, config-time:$CONFIG_TIME)"

