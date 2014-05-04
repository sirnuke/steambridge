#!/usr/bin/env python2.7

import os, shutil

import config, filesystem, appmanifest, appdb

class SetupException(Exception):
  def __init__(self, message):
    self._message = message

  def __str__(self):
    return self._message

# appid must be an integer
def do(appid):
  manifest = appmanifest.AppManifest(appid)

  if not manifest.exists():
    raise SetupException('{} lacks a manifest (try steambridge download {})'.format(appid, appid))

  if not manifest.parse():
    raise SetupException('Unable to parse the manifest for {}, it may be corrupted'.format(appid))

  if not manifest.is_ready():
    raise SetupException('{} is not fully downloaded yet'.format(appid))

  if not manifest.is_valid():
    raise SetupException('{} lacks the full manifest data'.format(appid))

  app = app.Entry(manifest.appid())
  app.installdir = manifest.installdir()
  app.name = manifest.name()

  # TODO: Get the icon from steam.  On Windows it's an icon, on Linux it's a
  #       zip containing pngs of the various sizes.  Stored in
  #       steam/games/<id>.zip (or .ico).  <id> isn't the appid however.
  #       SteamDb.info contains the metadata to know how <id> applies to
  #       appids (Information.clienticon).  However, it's not clear how
  #       to get this data. I believe SteamDb.info parses the internal
  #       data sent to Steam clients.
  # TODO: Once done, save that icon inside the appdb directory

  # Find the main executable
  app.executable = os.path.abspath(app.installdir + '/' + _find_executable(app.installdir))
  print "WARN: Using a temporary algorithm to find the main executable, found {}" \
      .format(app.executable)

  # Find the steam_api.dll and back it up
  st, dll = _process_output(filesystem.execute('find "{}" -name steam_api.dll' \
      .format(app.installdir)))

  if st == -1:
    raise SetupException("Didn't find a steam_api.dll in {}".format(app.installdir))
  elif st == -2:
    raise SetupException('Found mulitple steam_api.dlls in {}'.format(app.installdir))

  dll = os.path.abspath(dll)
  appdb.workingdir = os.path.dirname(dll)
  dllorig = dll + ".original"
  if not os.path.isfile(dllorig):
    shutil.copyfile(dll, dllorig)
  else:
    print "steam_api.dll.original already exists, not backing up..."

  # Get the API versions from the native steam_api.dll (Yuck, but it works consistently)
  app.setapiversion('user', _find_version(dllorig, \
      "SteamUser[[:digit:]]\{3\}", "SteamUser"))
  app.setapiversion('friends', _find_version(dllorig, \
      "SteamFriends[[:digit:]]\{3\}", "SteamFriends"))
  app.setapiversion('utils', _find_version(dllorig, \
      "SteamUtils[[:digit:]]\{3\}", "SteamUtils"))
  app.setapiversion('matchmaking', _find_version(dllorig, \
      "SteamMatchMaking[[:digit:]]\{3\}", "SteamMatchmaking"))
  app.setapiversion('matchmaking_servers', _find_version(dllorig, \
      "SteamMatchMakingServers[[:digit:]]\{3\}", "MatchmakingServers"))
  app.setapiversion('user_stats', _find_version(dllorig, \
      "STEAMUSERSTATS_INTERFACE_VERSION[[:digit:]]\{3\}", "SteamUserStats"))
  app.setapiversion('apps', _find_version(dllorig, \
      "STEAMAPPS_INTERFACE_VERSION[[:digit:]]\{3\}", "SteamApps"))
  app.setapiversion('networking', _find_version(dllorig, \
      "SteamNetworking[[:digit:]]\{3\}", "SteamNetworking"))
  app.setapiversion('remote_storage', _find_version(dllorig, \
      "STEAMREMOTESTORAGE_INTERFACE_VERSION[[:digit:]]\{3\}", \
      "SteamRemoteStorage"))
  app.setapiversion('screenshots', _find_version(dllorig, \
      "STEAMSCREENSHOTS_INTERFACE_VERSION[[:digit:]]\{3\}", "SteamScreenshots"))
  app.setapiversion('http', _find_version(dllorig, \
      "STEAMHTTP_INTERFACE_VERSION[[:digit:]]\{3\}", "SteamHTTP"))
  app.setapiversion('unified_messages', _find_version(dllorig, \
      "STEAMUNIFIEDMESSAGES_INTERFACE_VERSION[[:digit:]]\{3\}", \
      "SteamUnifiedMessages"))
  app.setapiversion('ugc', _find_version(dllorig, \
      "STEAMUGC_INTERFACE_VERSION[[:digit:]]\{3\}", "SteamUGC"))

  if not app.validate():
    err("Invalid appdb object! (internal error?)")

  # Save the appdb file
  app.save()

  # Create a .desktop file on the desktop
  desktop = os.path.expanduser("~") + "/Desktop/{}.desktop".format(manifest.appid())

  with open(desktop, 'w') as f:
    f.write("[Desktop Entry]\n")
    # TODO: Icon would go here
    f.write("Type=Application\n")
    f.write("Name={} (Wine)\n".format(app.name))
    f.write("Exec=steambridge execute {}\n".format(manifest.appid()))

  os.chmod(desktop, 0755)

  # Note that it's possible to add this to the shortcuts.vdf file
  # located... somewhere... in the Steam install.  Might be a better way to
  # go about this than creating a complete .desktop file.

  print "Done.  A newly created .desktop file should be on your desktop."


def _process_output(stdout):
  res = stdout.rstrip()
  if res == '':
    return False, 'NONE'
  if res.find('\n') != -1:
    return False, 'MULTIPLE'
  return True, res

def _find_version(dll, search, name):
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
def _find_executable(search):
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


