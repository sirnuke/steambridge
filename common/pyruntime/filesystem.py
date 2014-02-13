# filesystem.py - Stores various code related to the deployed filesystem

import os
import subprocess

# Root directory of the Steam installation
STEAM_ROOT = os.path.expanduser("~") + "/.steam/root"

# Directory storing the Steam appmanifest_*.acf files
STEAM_APPMANIFESTS = STEAM_ROOT + "/SteamApps"

# Common root of installed Steam games
STEAM_APPS = STEAM_ROOT + "/SteamApps/common"

# Root directory of the SteamBridge deployment
STEAM_BRIDGE_ROOT = STEAM_ROOT + "/SteamBridge"

# Location of the Win32 native steam_api proxy DLL
PROXY_DLL = STEAM_BRIDGE_ROOT + "/steam_api_proxy.dll"

# Location of the Winelib bridge library
BRIDGE_LIB = STEAM_BRIDGE_ROOT + "/steam_api_bridge.dll.so"

# Location of the native Linux steam_api library
STEAM_API_LIB = STEAM_BRIDGE_ROOT + "/libsteam_api.so"

# The root directory of the internal AppDB
APPDB_ROOT = STEAM_BRIDGE_ROOT + "/appdb"

_STEAM_DIRS = [STEAM_ROOT, STEAM_APPMANIFESTS, STEAM_APPS]
_STEAM_FILES = []
_BRIDGE_DIRS = [STEAM_BRIDGE_ROOT, APPDB_ROOT]
_BRIDGE_FILES = [PROXY_DLL, BRIDGE_LIB, STEAM_API_LIB]

# TODO: Handle error cases better.  Exceptionz
def validate():
  for i in _STEAM_DIRS:
    if not os.path.isdir(i):
      print "Missing expected Steam directory {}".format(i)
      return False

  for i in _STEAM_FILES:
    if not os.path.isfile(i):
      print "Missing expected Steam file {}".format(i)
      return False

  for i in _BRIDGE_DIRS:
    if not os.path.isdir(i):
      print "Missing expected SteamBridge directory {}".format(i)
      return False

  for i in _BRIDGE_FILES:
    if not os.path.isfile(i):
      print "Missing expected SteamBridge file {}".format(i)
      return False

  return True

def execute(command):
  return subprocess.check_output(command, shell=True)

