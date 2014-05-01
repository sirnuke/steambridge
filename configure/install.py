#!/usr/bin/env python2.7
# install.py - Installs SteamBridge to the user's system
# Copyright (c) 2014 Bryan DeGrendel
#
# See COPYING and license/LICENSE.steambridge for license information

import os
import subprocess

from utilities import execute, error, Options

options = Options()
options.load()
config = options.configure()

build = config['steambridge']['build']
prefix = config['steambridge']['prefix']

if not os.path.isfile(build['bridge_lib']):
  error("Install", "Winelib bridge library isn't compiled (run make)!")

if not os.path.isfile(build['proxy_dll']):
  error("Install", "Win32 proxy library isn't found")

try:
  # os.makedirs raise an exception(!) if the directory already exists
  # Thanks Python!
  execute('mkdir -p {}'.format(prefix['shared']))
  execute('mkdir -p {}'.format(prefix['bin']))
  execute('mkdir -p {}'.format(prefix['pysteambridge']))
  execute('mkdir -p {}'.format(prefix['winedllpath']))
  execute('mkdir -p {}'.format(prefix['documentation']))
  execute('mkdir -p {}'.format(prefix['licenses']))

  # shutils.copy and friends seem to work kinda weird and not Unixy, so just use the system cp
  cp = 'cp --no-preserve=mode {} {}'
  execute(cp.format(build['bridge_lib'], prefix['bridge_lib']))
  execute(cp.format(build['proxy_dll'], prefix['proxy_dll']))
  execute(cp.format(build['steam_api_lib'], prefix['steam_api_lib']))
  execute(cp.format(build['executable'], prefix['executable']))
  execute(cp.format(build['pysteambridge'], prefix['pysteambridge']))
  execute(cp.format(build['documentation'], prefix['documentation']))
  execute(cp.format(build['licenses'], prefix['licenses']))

  # Set permissions
  execute('chmod +x {}'.format(prefix['executable']))

  # Create the version file
  version_file = open(prefix['version'], 'w')
  version_file.write(config['steambridge']['version']['long'])
  version_file.close()

except subprocess.CalledProcessError as e:
  error("Install", "Error while running command: {}".format(e))

