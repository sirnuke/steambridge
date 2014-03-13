#!/bin/bash
#
# Defines various constants used in the entirety of shell scripting.
# To override any values, copy this file to common/local.sh and modify
# as you see fit.

# Root directory of the local steam installation
STEAM_ROOT=~/.steam/root

# Location of appmanifest_*.acf files
STEAM_APPMANIFESTS=$STEAM_ROOT/SteamApps

# Common root of installed Steam games
STEAM_APPS=$STEAM_ROOT/SteamApps/common

# Root directory of the SteamBridge deployment
STEAM_BRIDGE_ROOT=$STEAM_ROOT/SteamBridge

# Configuration filename, used by the C++ library
CONFIG_FILENAME=$STEAM_BRIDGE_ROOT/config.json

# Location of the Win32 native steam_api proxy DLL
# This is the location when it's deployed
PROXY_DLL=$STEAM_BRIDGE_ROOT/steam_api_proxy.dll

# Location of the Winelib bridge library
BRIDGE_LIB=$STEAM_BRIDGE_ROOT/steam_api_bridge.dll.so

# Location of Winelib DLLs, used as WINEDLLPATH
WINELIB_PATH=$STEAM_BRIDGE_ROOT

# Location of the native Linux steam_api library
STEAM_API_LIB=$STEAM_BRIDGE_ROOT/libsteam_api.so

# Root directory of the internal AppDB
APPDB_ROOT=$STEAM_BRIDGE_ROOT/appdb

# AppDB configuration filename
APPDB_CONFIG=appdb.json

# Directory storing the SteamBridge tools
TOOLS_DIR=$STEAM_BRIDGE_ROOT/bin

# Directory storing the Python Runtime library
PYRUNTIME_DIR=$TOOLS_DIR/pyruntime

# Location of the execute tool script
EXECUTE_TOOL=$TOOLS_DIR/execute.py

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
MACHINE_HOSTNAME=`hostname|sed -e 's/[ ]*$//'`

VERSION_SHORT="$VERSION_MAJOR.$VERSION_MINOR.$VERSION_PATCH"
VERSION_LONG="$VERSION_MAJOR.$VERSION_MINOR.$VERSION_PATCH (git-head:$GIT_HEAD, config-time:$CONFIG_TIME, hostname:$MACHINE_HOSTNAME)"

