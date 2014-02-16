#!/bin/bash

. ./common/settings.sh

# Files
bridgelib=bridge/steam_api_bridge.dll/steam_api_bridge.dll.so
steamapilib=common/steam/libsteam_api.so
proxydllname=steam_api_proxy.dll
pylib=`find common/pyruntime/ -name *.py`
tools=`find tools/ -name *.py`

# Argument settings
clean=false

if [ $EUID -eq 0 ] ; then
  echo "$0: Don't run as root!"
  exit 1
fi

if [ ! -f "$bridgelib" ] ; then
  echo "$0: The Winelib Bridge library isn't compiled!"
  exit 1
fi

if [ ! -f "common/pyruntime/config.py" ] ; then
  echo "$0: $APP_NAME isn't configured (make config)"
  exit 1
fi

proxydll=`find . -name "$proxydllname"`
if [ `echo "$proxydll" | wc -l` -gt 1 ] ; then
  echo "$0: Found multiple $proxydllname DLLs!"
  exit 1
fi
if [ -z "$proxydll" ] ; then
  echo "$0: No $proxydllname found!"
  echo "Compile it on Windows/Visual Studio, and copy it to the tree"
  exit 1
fi

if [ ! -d $STEAM_ROOT ] ; then
  echo "$0: '$STEAM_ROOT' not found - Linux Steam not installed?"
  exit 1
fi

for arg in "$@"; do
  if [ $arg = "--help" -o $arg = "-h" ] ; then
    echo "$0 [--help|-h] [--clean]"
    echo ""
    echo "   --clean   Delete existing deployment beforehand"
    echo "   --help    This help message"
    exit 0
  elif [ $arg = "--clean" ] ; then
    clean=true
  else
    echo "$0: Unknown argument $arg"
    exit 1
  fi
done

if $clean ; then
  rm -rf $STEAM_BRIDGE_ROOT
fi

mkdir -p $STEAM_BRIDGE_ROOT
mkdir -p $WINELIB_PATH
mkdir -p $APPDB_ROOT
mkdir -p $TOOLS_DIR
mkdir -p $PYRUNTIME_DIR

# As a minor safety mark, as both may default to executable bit set
# Yes, it's more ideal to modify the copied files than the sources.
chmod -x $bridgelib
chmod -x $proxydll

cp $bridgelib $BRIDGE_LIB
cp $steamapilib $STEAM_API_LIB
cp $proxydll $PROXY_DLL
echo $VERSION_LONG > $STEAM_BRIDGE_ROOT/steam-bridge-version.txt
cp $tools $TOOLS_DIR
cp $pylib $PYRUNTIME_DIR

echo "$0: Deployed"

