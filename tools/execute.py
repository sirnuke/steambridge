#!/usr/bin/env python2.7

import argparse

from pyruntime import filesystem, appdb

parser = argparse.ArgumentParser()
parser.add_argument("appid", help="run this Steam game using Wine")
args = parser.parse_args()

def err(message):
  print message
  exit(1)

appdb = appdb.Entry(str(args.appid))

if appdb.exists() == False:
  err("{} doesn't appear to be configured".format(appid))

appdb.load()

# Enter the 'working' directory of `appid`
# Copy the proxy dll to steam_api.dll
# If steam_appid.txt exists and differs in expected value, back it up
# Write out steam_appid.txt containing `appid`
# Execute using WINEDEBUG="..." WINEPREFIX="..." WINEDLLPATH="..." wine app 2>... >...
