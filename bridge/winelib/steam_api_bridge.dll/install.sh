#!/bin/sh
# TODO: Get paths and versions from source plz
INSTALLDIR=~/.steam/root/steam_bridge
VERSION="0.0.1"
if [ -e $INSTALLDIR ] ; then
  read -p "Overwrite installation directory? " yn
  case $yn in
    [Yy]* ) rm -rf $INSTALLDIR;;
    * ) echo "Aborting"; exit;;
  esac
fi
mkdir -p $INSTALLDIR
cp ../../../steam/libsteam_api.so $INSTALLDIR
cp appid_db.cfg $INSTALLDIR
echo $VERSION > $INSTALLDIR/version.txt
echo "Fin"
