# appmanifest.py - Wraps around ACF appmanifest files

import re
import os

import config

class AppManifest:
  def __init__(self, appid):
    if appid <= 0:
      print "Invalid appid of {}".format(appid)
      exit(1)

    self._filename = config.STEAM_APPMANIFESTS \
        + "/appmanifest_{}.acf".format(appid)
    self._name = None
    self._state = None
    self._installdir = None
    self._appid = appid

    if not os.path.isfile(self._filename):
      self._exists = False
    else:
      self._exists = True

  def parse(self):
    if self._exists == False:
      return false

    with open(self._filename, 'r') as f:
      # TODO: This is like 1/3 of the work necessary to fully parse
      #       ACF files.  It'd be better (and less brittle) to do so
      # TODO: A '\"' can be used in certain situations
      keyvalue = \
          re.compile("^\s*\"(?P<key>[^\"]+)\"\s*\"(?P<value>[^\"]+)\"\s*$")
      for line in f:
        r = keyvalue.search(line)

        if r != None:
          data = r.groupdict()

          if data['key'] == 'AppID':
            if int(data['value']) != self._appid:
              print "ERROR: Expecting appid of {}, found {}" \
                  .format(appid, data['value'])
              exit(1)

          elif data['key'] == 'StateFlags':
            self._state = data['value']

          elif data['key'] == 'name':
            # The files may (might (will)) contain multiple "name" directives
            # As it seems to be consistently the same value, this is a quick
            # hack and to use the first one:
            if self._name == None:
              self._name = data['value']

          elif data['key'] == 'installdir':
            self._installdir = config.STEAM_APPS \
                + "/{}".format(data['value'])

    # For now, only require a state
    if self._state == None:
      return False

    return True

  def is_ready(self):
    if self._state == '4':
      return True
    return False

  def is_valid(self):
    if self._installdir == None or self._name == None or self._state == None:
      return False
    return True

  def exists(self):
    return self._exists

  def filename(self):
    return self._filename

  def installdir(self):
    return self._installdir

  def name(self):
    return self._name

  def appid(self):
    return self._appid
