# utilities.py - Utility code shared between various configuration and installation scripts
# Copyright (c) 2014 Bryan DeGrendel
#
# See COPYING and license/LICENSE.steambridge for license information

import json
import os
import subprocess

class Options:
  def __init__(self):
    self._data =  {
                    'steam_root': '~/.steam/root',
                    'prefix'    : '/usr/local',
                    'local'     : '~/.steam/root/SteamBridge',
                  }
    self._filename = '.configuration.json'
    self._version = [0, 0, 2, 'dev']

  # Attempt to load the options
  # Returns False on error (typically means source file isn't found)
  def load(self):
    if not os.path.isfile(self._filename):
      error("Options", "'{}' isn't readable! (did you run 'make config'?)".format(self._filename))
    try:
      options_cache = open(self._filename, 'r')
      self._data = json.load(options_cache)
      options_cache.close()
    except IOError, e:
      error("Options", "IOError while reading '{}': {}".format(self._filename, e))

  # Save the options
  # Does NOT save the generated configuration values
  def save(self):
    try:
      options_cache = open(self._filename, 'w')
      json.dump(self._data, options_cache)
      options_cache.close()
    except IOError, e:
      error("Options", "IOError while writing '{}': {}".format(self._filename, e))

  # Return the value for an option
  def get(self, key):
    return self._data[key]

  # Set a option
  def set(self, key, value):
    self._data[key] = value

  # Returns an array mapping various configured values
  def configure(self):
    steam_root = self.get('steam_root')
    prefix = self.get('prefix')
    local = self.get('local')
    shared = prefix + '/share/steambridge'
    doc = prefix + '/share/doc/steambridge'
    _bin = prefix + '/bin'

    version_major = self._version[0]
    version_minor = self._version[1]
    version_patch = self._version[2]
    version_extra = self._version[3]

    config_time = execute('date').strip()
    git_head = execute('git rev-parse HEAD').strip()

    return  {
              'steam':
              {
                # Root directory of the local Steam installation.
                'root': steam_root,
                # Directory storing app manifest files
                'app_manifests': steam_root + '/SteamApps',
                # Common root directory of installed applications
                'apps': steam_root + '/SteamApps/common',
              },
              'steambridge':
              {
                'app_name': 'SteamBridge',
                'copyright': 'Bryan DeGrendel (c) 2014',
                'license': 'See COPYING and license directory for information',
                'webpage': 'https://github.com/sirnuke/steambridge',
                'version':
                {
                  'major': version_major,
                  'minor': version_minor,
                  'patch': version_patch,
                  'extra': version_extra,
                  'short': '{}.{}.{}-{}'.format(version_major, version_minor, version_patch,
                    version_extra),
                  'long' : '{}.{}.{}-{} (git-head:{}, config-time:{})'.format(version_major,
                    version_minor, version_patch, version_extra, git_head, config_time),
                },
                # 'local' scope defines locations modified and used by the current user.
                'local':
                {
                  # Root directory of the user's local SteamBridge files.
                  'root': local,
                  # User's local configuration file
                  'config': local + '/configuration.json',
                  # Root directory of the user's application tracking files.
                  'appdb': local + '/appdb',
                  # Filename (not path) of an application's appdb entry.
                  'appdb_config_filename': 'appdb.json',
                },
                # 'prefix' scope defines static files installed (potentially) system wide.
                'prefix':
                {
                  # Root directory of the static, installed SteamBridge files.
                  'root': prefix,
                  # Shared directory storing non-executable files.
                  'shared': shared,
                  # Absolute path to add to WINEDLLPATH
                  'winedllpath': shared,
                  # Location to install the Winelib Bridge library.
                  # This MUST be in the same directory as winedllpath.  In the future we'll
                  # handle this better.
                  'bridge_lib': shared + '/steam_api_bridge.dll.so',
                  # Location to store the distributed copy of Steam's API Linux library.
                  # Do NOT install this file anywhere ld.so will find it.  It may interfere
                  # with native Steam applications, who package their own copy.
                  'steam_api_lib': shared + '/libsteam_api.so',
                  # Location to install the Proxy DLL.
                  # NOTE: This file is found (in the source tree) using find.
                  'proxy_dll': shared + '/steam_api_proxy.dll',
                  # Root directory of the runtime python code.
                  # NOTE: This directory's name and relativeness to _bin must be static, in
                  # order for the main steambridge.py script to find it.  Stay tuned for a
                  # less brittle solution.
                  'pysteambridge': shared + '/pysteambridge',
                  # Directory to store client executable files.
                  'bin': _bin,
                  # Location to install the main steambridge.py script.
                  'executable': _bin + '/steambridge',
                },
              },
            }

# Executes a shell command.  If ignore_results is True, then subprocess exceptions are caught and
# ignored.  This is helpful when the command may return non-zero and succeed.  stdout is returned.
# TODO: Share this code somehow with the pysteambridge runtime?
# TODO: Better ignore_results behavior.  Still throw exceptions on certain errors?
def execute(command, ignore_results = False):
  if not ignore_results:
    return subprocess.check_output(command, shell=True)
  else:
    try:
      return subprocess.check_output(command, shell=True)
    except subprocess.CalledProcessError as e:
      return e.output

def error(tag, message):
  print "Error! [{}]: {}".format(tag, message)
  exit(1)

