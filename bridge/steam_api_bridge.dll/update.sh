#!/bin/sh
# TODO: Get paths and versions from source plz
INSTALLDIR=~/.steam/root/SteamBridge
VERSION="0.0.1"
if [ ! -e steam_api_bridge.dll.so ] ; then
  echo "steam_api_bridge.dll.so not found, compile it with 'make'"
  exit
fi
if [ ! -e $INSTALLDIR ] ; then
  mkdir $INSTALLDIR
fi
if [ ! -d /usr/lib/i386-linux-gnu/wine ] ; then
  echo "The expected 32-bit Wine DLL directory doesn't exist!"
  echo "You'll need to copy steam_api_bridge.dll.so somewhere it can be found by Wine"
else
  sudo cp steam_api_bridge.dll.so /usr/lib/i386-linux-gnu/wine/
fi
cp ../../common/steam/libsteam_api.so $INSTALLDIR
cp appid_db.cfg $INSTALLDIR
echo $VERSION > $INSTALLDIR/version.txt
echo "Fin"
