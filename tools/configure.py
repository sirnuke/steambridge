#!/usr/bin/env python2.7

import argparse
import os
import shutil

from pyruntime import filesystem, appmanifest, appdb

parser = argparse.ArgumentParser()
parser.add_argument("appid", help="the application's id")
args = parser.parse_args()

manifest = appmanifest.AppManifest(int(args.appid))
appid = str(manifest.appid())

def err(message):
  print message
  exit(1)

def process_output(stdout):
  res = stdout.rstrip()
  if res == '' or res.find('\n') != -1:
    return None
  return res

if not manifest.exists():
  err("{} lacks a manifest! (run download.py first)".format(appid))

if not manifest.parse():
  err("Unable to parse {}'s manifest, it may be corrupted".format(appid))

if not manifest.is_ready():
  err("{} is not fully downloaded".format(appid))

if not manifest.is_valid():
  err("{} lacks the full manifest data".format(appid))

appdb = appdb.Entry(manifest.appid())
appdb.installdir = manifest.installdir()

# TODO: Get the icon from steam.  On Windows it's an icon, on Linux it's a
#       zip containing pngs of the various sizes.  Stored in
#       steam/games/<id>.zip (or .ico).  <id> isn't the appid however.
#       SteamDb.info contains the metadata to know how <id> applies to
#       appids (Information.clienticon).  However, it's not clear how
#       to get this data. I believe SteamDb.info parses the internal
#       data sent to Steam clients.
# TODO: Once done, save that icon inside the appdb directory

# Find the steam_api.dll and back it up
stdout = filesystem.execute("find {} -name steam_api.dll".format(appdb.installdir))
dll = process_output(stdout)

if dll == None:
  err("Didn't find exactly one steam_api.dll in {}".format(appdb.installdir))

dll = os.path.abspath(dll)
appdb.workingdir = os.path.dirname(dll)
if not os.path.isfile(dll + ".original"):
  shutil.copyfile(dll, dll + ".original")
else:
  print "steam_api.dll.original already exists, not backing up..."

# TODO: Get API versions using 'strings steam_api.dll|grep BLANK
# TODO: Store all this metadata
# TODO: Create a .desktop file that points to execute.py, and later the icon

