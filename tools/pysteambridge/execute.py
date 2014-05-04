# execute.py - API for running an application
# Copyright (c) 2014 Bryan DeGrendel
#
# See COPYING and license/LICENSE.steambridge for license information

import os, shutil

import config, filesystem, appdb

class ExecuteException(Exception):
  def __init__(self, message):
    self._message = message

  def __str__(self):
    return self._message

# appid must be an integer
def do(appid):
  app = appdb.Entry(appid)
  if not app.exists():
    raise ExecuteException("{} isn't configured (steambridge setup {})".format(appid, appid))

  app.load()

  if not app.validate():
    raise ExecuteException("{} has an invalid internal configuration, try rerunning setup" \
        .format(appid))

  # Copy the proxy DLL
  shutil.copyfile(config.PROXY_DLL, app.workingdir + "/steam_api.dll")

  # Set appid.txt, if it doesn't already exist
  # TODO: Check to make sure the existing appid.txt has the right value?
  if not os.path.isfile(app.workingdir + "/steam_appid.txt"):
    with open(app.workingdir + "/steam_appid.txt", 'w') as f:
      f.write(app.appid())

  # Change to the installation directory and execute using wine
  os.chdir(app.installdir)
  # TODO: wineprefix
  cmd = 'WINEDEBUG="+steambridge" WINEDLLPATH="{}" wine "{}" 2>"{}/stderr.txt" >"{}/stdout.txt"' \
      .format(config.WINELIB_PATH, app.executable, appdb.directory(), appdb.directory())

  print "DEBUG: execute('{}')".format(cmd)

  filesystem.execute(cmd, ignore_results=True)

