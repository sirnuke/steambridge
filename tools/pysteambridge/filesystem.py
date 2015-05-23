# filesystem.py - Stores various code related to the deployed filesystem

import os
import subprocess

import config

_STEAM_DIRS = [config.STEAM_ROOT]
_MAKE_DIRS = [config.STEAM_APPMANIFESTS, config.STEAM_APPS, config.STEAM_BRIDGE_LOCAL,
    config.APPDB_ROOT]
_BRIDGE_FILES = [config.PROXY_DLL, config.BRIDGE_LIB, config.STEAM_API_LIB]

class FilesystemException(Exception):
  def __init__(self, type, path, hint):
    self._type = type
    self._path = path
    self._hint = hint

  def __str__(self):
    return "{} may be corrupt; '{}' not found ({})" \
        .format(self._type, self._path, self._hint)

def validate():
  for i in _STEAM_DIRS:
    if not os.path.isdir(i):
      raise FilesystemException('Steam', i, "Is Linux Steam properly installed?")

  for i in _BRIDGE_FILES:
    if not os.path.isfile(i):
      raise FilesystemException(config.APP_NAME, i, "Is SteamBridge properly installed?")

  for i in _MAKE_DIRS:
    if not os.path.isdir(i):
      os.makedirs(i)

def execute(command, ignore_results = False):
  if not ignore_results:
    return subprocess.check_output(command, shell=True)
  else:
    try:
      return subprocess.check_output(command, shell=True)
    except subprocess.CalledProcessError as e:
      return e.output

