# appdb.py - Wraps around an internal appdb state

import json
import os

import config

class Entry:
  def __init__(self, appid):
    self.installdir = None
    self.workingdir = None
    self.executable = None
    self.name = None
    self._appid = appid
    self._directory = config.APPDB_ROOT + "/" + str(appid)
    self._filename = self._directory + "/appdb.json"
    self._apiversions = {}

    if not os.path.isdir(self._directory):
      os.mkdir(self._directory)

  def validate(self):
    if not self.installdir or not self.workingdir or not self.name or not self.executable:
      return False
    return True

  def setapiversion(self, api, version):
    self._apiversions[api] = version

  def save(self):
    data = { 'appid' : self._appid,     'name'        : self.name,
        'executable' : self.executable, 'installdir'  : self.installdir,
        'workingdir' : self.workingdir, 'apiversions' : self._apiversions }
    with open(self._filename, 'w') as f:
      json.dump(data, f)

  def load(self):
    with open(self._filename, 'r') as f:
      data = json.load(f)
    if self._appid != data['appid']:
      print "Warning: {}'s appdb file has the wrong appid value of {}" \
          .format(data['appid'], self._appid)
    self.name = data['name']
    self.installdir = data['installdir']
    self.workingdir = data['workingdir']
    self.executable = data['executable']
    self._apiversions = data['apiversions']

  def exists(self):
    return os.path.isfile(self._filename)

  def directory(self):
    return self._directory

  def appid(self):
    return self._appid


