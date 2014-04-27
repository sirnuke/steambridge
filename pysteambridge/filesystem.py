# filesystem.py - Stores various code related to the deployed filesystem

import os
import subprocess

import config

_STEAM_DIRS = [config.STEAM_ROOT, config.STEAM_APPMANIFESTS, config.STEAM_APPS]
_STEAM_FILES = []
_BRIDGE_DIRS = [config.STEAM_BRIDGE_ROOT, config.APPDB_ROOT, config.TOOLS_DIR]
_BRIDGE_FILES = [config.PROXY_DLL, config.BRIDGE_LIB, config.STEAM_API_LIB,
    config.EXECUTE_TOOL]

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

def execute(command, ignore_results = False):
  if not ignore_results:
    return subprocess.check_output(command, shell=True)
  else:
    try:
      return subprocess.check_output(command, shell=True)
    except subprocess.CalledProcessError as e:
      return e.output

