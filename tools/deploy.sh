#!/bin/bash
# Directories:
rootdir=~/.steam/root
bridgedir=$rootdir/SteamBridge

# Stores internal tools provided
toolsdir=$bridgedir/bin
# Stores internal state data about installed applications
appdbdir=$bridgedir/appdb
# Python library for shared code between the internal tools
pylibdir=$toolsdir/pyruntime

# Files
bridgelib=bridge/steam_api_bridge.dll/steam_api_bridge.dll.so
steamapilib=common/steam/libsteam_api.so
proxydllname=steam_api_proxy.dll
versiontxt=common/VERSION.txt
pylib=`find common/pyruntime/ -name *.py`
tools=`find tools/ -name *.py`

# Argument settings
clean=false

if [ $EUID -eq 0 ] ; then
  echo "$0: Don't run as root!"
  exit 1
fi

if [ ! -f $bridgelib ] ; then
  echo "$0: The Winelib Bridge library isn't compiled!"
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

if [ ! -d $rootdir ] ; then
  echo "$0: '$rootdir' not found - Linux Steam not installed?"
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
  rm -rf $bridgedir
fi

mkdir -p $bridgedir
mkdir -p $toolsdir
mkdir -p $appdbdir
mkdir -p $pylibdir

# As a minor safety mark, as both may default to executable bit set
# Yes, it's more ideal to modify the copied files than the sources.
chmod -x $bridgelib
chmod -x $proxydll

cp $bridgelib $bridgedir
cp $steamapilib $bridgedir
cp $proxydll $bridgedir
cp $versiontxt $bridgedir
cp $tools $toolsdir
cp $pylib $pylibdir

echo "$0: Deployed"

