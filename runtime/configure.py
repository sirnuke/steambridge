#!/usr/bin/env python2.7

import argparse
import os
import shutil

from pyruntime import config, filesystem, appmanifest, appdb

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
  if res == '':
    return False, 'NONE'
  if res.find('\n') != -1:
    return False, 'MULTIPLE'
  return True, res

def find_version(dll, search, name):
  st, api = process_output(filesystem.execute( \
    'strings "{}" | grep "^{}$" || true'.format(dll, search)))
  if st == False and api == 'Multiple':
    err("Found multiple API version strings for '{}'".format(name))
  if st == False:
    return None
  return api

# This is a holdover algorithm until appcache/appinfo.vdf is
# readable. This file appears to be a compiled version of the keyvalue
# format Valve loves oh so much.  It specifically contains various metadata,
# possibly including the icon data.
def find_executable(search):
  # First, look for any executables in the root directory
  exes = filesystem.execute('ls "{}" | grep "\\.exe$" || true'.format(search)) \
      .rstrip().split('\n')

  # Didn't find any?  Do a recursive find
  if len(exes) == 1 and exes[0] == '':
    exes = filesystem.execute('ls -R "{}" | grep "\\.exe$" || true' \
        .format(search)).rstrip().split('\n')
    if len(exes) == 1 and exes[0] == '':
      err("Unable to find any executable (*.exe) files")

  if len(exes) == 1:
    return exes[0]

  # Look for something that appears to link against steam_api.dll
  options = []
  for exe in exes:
    stdout = filesystem.execute( \
        'strings "{}" | grep "steam_api\\.dll" || true' \
        .format(os.path.abspath(search + '/' + exe))).rstrip()
    if stdout != '':
      options.append(exe)

  if len(options) == 1:
    return options[0]

  # If nothing seems to link against steam_api.dll, compare all executables
  if len(options) == 0:
    options = exes

  # And default to the largest one, which probably isn't correct
  # Actually, the smallest miiight be the better option
  final = None
  size = 0
  for exe in options:
    s = os.path.getsize(exe)
    if s > size:
      final = exe
      size = s

  return final

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
appdb.name = manifest.name()

# TODO: Get the icon from steam.  On Windows it's an icon, on Linux it's a
#       zip containing pngs of the various sizes.  Stored in
#       steam/games/<id>.zip (or .ico).  <id> isn't the appid however.
#       SteamDb.info contains the metadata to know how <id> applies to
#       appids (Information.clienticon).  However, it's not clear how
#       to get this data. I believe SteamDb.info parses the internal
#       data sent to Steam clients.
# TODO: Once done, save that icon inside the appdb directory

# Find the main executable
appdb.executable = os.path.abspath(appdb.installdir + '/' \
    + find_executable(appdb.installdir))
print "WARN: Using a temporary algorithm to find the main executable"
print "Found {}".format(appdb.executable)

# Find the steam_api.dll and back it up
st, dll = process_output(filesystem.execute('find "{}" -name steam_api.dll' \
    .format(appdb.installdir)))

if st == -1:
  err("Didn't find a steam_api.dll in {}".format(appdb.installdir))
elif st == -2:
  err("Found mulitple steam_api.dlls in {}".format(appdb.installdir))

dll = os.path.abspath(dll)
appdb.workingdir = os.path.dirname(dll)
dllorig = dll + ".original"
if not os.path.isfile(dllorig):
  shutil.copyfile(dll, dllorig)
else:
  print "steam_api.dll.original already exists, not backing up..."

# Get the API versions from the native steam_api.dll
appdb.setapiversion('user', find_version(dllorig, \
    "SteamUser[[:digit:]]\{3\}", "SteamUser"))
appdb.setapiversion('friends', find_version(dllorig, \
    "SteamFriends[[:digit:]]\{3\}", "SteamFriends"))
appdb.setapiversion('utils', find_version(dllorig, \
    "SteamUtils[[:digit:]]\{3\}", "SteamUtils"))
appdb.setapiversion('matchmaking', find_version(dllorig, \
    "SteamMatchMaking[[:digit:]]\{3\}", "SteamMatchmaking"))
appdb.setapiversion('matchmaking_servers', find_version(dllorig, \
    "SteamMatchMakingServers[[:digit:]]\{3\}", "MatchmakingServers"))
appdb.setapiversion('user_stats', find_version(dllorig, \
    "STEAMUSERSTATS_INTERFACE_VERSION[[:digit:]]\{3\}", "SteamUserStats"))
appdb.setapiversion('apps', find_version(dllorig, \
    "STEAMAPPS_INTERFACE_VERSION[[:digit:]]\{3\}", "SteamApps"))
appdb.setapiversion('networking', find_version(dllorig, \
    "SteamNetworking[[:digit:]]\{3\}", "SteamNetworking"))
appdb.setapiversion('remote_storage', find_version(dllorig, \
    "STEAMREMOTESTORAGE_INTERFACE_VERSION[[:digit:]]\{3\}", \
    "SteamRemoteStorage"))
appdb.setapiversion('screenshots', find_version(dllorig, \
    "STEAMSCREENSHOTS_INTERFACE_VERSION[[:digit:]]\{3\}", "SteamScreenshots"))
appdb.setapiversion('http', find_version(dllorig, \
    "STEAMHTTP_INTERFACE_VERSION[[:digit:]]\{3\}", "SteamHTTP"))
appdb.setapiversion('unified_messages', find_version(dllorig, \
    "STEAMUNIFIEDMESSAGES_INTERFACE_VERSION[[:digit:]]\{3\}", \
    "SteamUnifiedMessages"))
appdb.setapiversion('ugc', find_version(dllorig, \
    "STEAMUGC_INTERFACE_VERSION[[:digit:]]\{3\}", "SteamUGC"))

if not appdb.validate():
  err("Invalid appdb object! (internal error?)")

# Save the appdb file
appdb.save()

# Create a .desktop file on the desktop
desktop = os.path.expanduser("~") \
    + "/Desktop/{}.desktop".format(manifest.appid())

with open(desktop, 'w') as f:
  f.write("[Desktop Entry]\n")
  # TODO: Icon would go here
  f.write("Type=Application\n")
  f.write("Name={} (Wine)\n".format(appdb.name))
  f.write("Exec={} {}\n".format(config.EXECUTE_TOOL, manifest.appid()))

os.chmod(desktop, 0755)

# Note that it's possible to add this to the shortcuts.vdf file
# located... somewhere... in the Steam install.  Might be a better way to
# go about this than creating a complete .desktop file.

print "Done.  A newly created .desktop file should be on your desktop."

