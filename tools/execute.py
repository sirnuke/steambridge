#!/usr/bin/env python2.7

import argparse
import shutil
import os

from pyruntime import config, filesystem, appdb

parser = argparse.ArgumentParser()
parser.add_argument("appid", help="run this Steam game using Wine")
args = parser.parse_args()

def err(message):
  print message
  exit(1)

appdb = appdb.Entry(str(args.appid))

if appdb.exists() == False:
  err("{} doesn't appear to be configured".format(appdb.appid()))

appdb.load()

if not appdb.validate():
  err("{} has an invalid appdb file".format(appdb.appid()))

# Copy the proxy DLL
shutil.copyfile(config.PROXY_DLL, appdb.workingdir + "/steam_api.dll")

# Set appid.txt, if it doesn't already exist
# TODO: Check to make sure the existing appid.txt has the right value?
if not os.path.isfile(appdb.workingdir + "/steam_appid.txt"):
  with open(appdb.workingdir + "/steam_appid.txt", 'w') as f:
    f.write(appdb.appid())

# Change to the installation directory and execute using wine
os.chdir(appdb.installdir)
# TODO: wineprefix
cmd = 'WINEDEBUG="+steambridge" WINEDLLPATH="{}" wine "{}" 2>"{}/stderr.txt" >"{}/stdout.txt"' \
    .format(config.WINELIB_PATH, appdb.executable, appdb.directory(), appdb.directory())

print "DEBUG: execute('{}')".format(cmd)

filesystem.execute(cmd, ignore_results=True)

