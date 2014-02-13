#!/usr/bin/env python2.7

import argparser
import os

from pyruntime import filesystem, appmanifest, appdb

parser = argparse.ArgumentParser()
parser.add_argument("appid", help="the application's id")
args = parser.parse_args()

manifest = filesystem.AppManifest(int(args.appid))
appid = str(manifest.appid())

def err(message):
  print message
  exit(1)

if not manifest.exists():
  err("{} lacks a manifest! (run download.py first)".format(appid))

if not manifest.parse():
  err("Unable to parse {}'s manifest, it may be corrupted".format(appid))

if not manifest.is_ready():
  err("{} is not fully downloaded".format(appid))

appdb.cd_into(appid)

# TODO: Get the icon from steam.  On Windows it's an icon, on Linux it's a
#       zip containing pngs of the various sizes.  Stored in
#       steam/games/<id>.zip (or .ico).  <id> isn't the appid however.
#       SteamDb.info contains the metadata to know how <id> applies to
#       appids (Information.clienticon).  However, it's not clear how
#       to get this data. I believe SteamDb.info parses the internal
#       data sent to Steam clients.
# TODO: Once done, save that icon here

# TODO: Find where the win32 app stores steam_api.dll.  Back it up.
# TODO: Get API versions using 'strings steam_api.dll|grep BLANK
# TODO: Store all this metadata
# TODO: Create a .desktop file that points to execute.py, and later the icon

