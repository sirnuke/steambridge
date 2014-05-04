# filesystem.py - Stores various code related to the deployed filesystem

import os
import subprocess

import config

_STEAM_DIRS = [config.STEAM_ROOT, config.STEAM_APPMANIFESTS, config.STEAM_APPS]
_BRIDGE_DIRS = [config.STEAM_BRIDGE_LOCAL, config.APPDB_ROOT] 
_BRIDGE_FILES = [config.PROXY_DLL, config.BRIDGE_LIB, config.STEAM_API_LIB]

class FilesystemException(Exception):
  def __init__(self, type, path):
    self._type = type
    self._path = path

  def __str__(self):
    return "Missing {} path '{}'".format(self._type, self._path)

def validate():
  for i in _STEAM_DIRS:
    if not os.path.isdir(i):
      raise FilesystemException('steam', i)

  for i in _BRIDGE_FILES:
    if not os.path.isfile(i):
      raise FilesystemException('steambridge', i)

  for i in _BRIDGE_DIRS:
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

