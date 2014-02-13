# appdb.py - Wraps around an internal appdb state

import os

import filesystem

class AppDBEntry:
  def __init__(self, appid):
    self.installdir = None
    self._appid = appid
    self._directory = filesystem.APPDB_ROOT + str(appid)

    if not os.path.isdir(self._directory):
      os.mkdir(self._directory)

  def validate(self):
    if self.installdir == None:
      return False
    return True


