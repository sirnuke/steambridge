# appdb.py - Wraps around an internal appdb state

import os

import filesystem

class Entry:
  def __init__(self, appid):
    self.installdir = None
    self.workingdir = None
    self._appid = appid
    self._directory = filesystem.APPDB_ROOT + str(appid)
    self._apiversions = {}

    if not os.path.isdir(self._directory):
      os.mkdir(self._directory)

  def validate(self):
    if self.installdir == None or self.workingdir == None:
      return False
    return True

  def setapiversion(self, api, version):
    self._apiversions[api] = version


