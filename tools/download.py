#!/usr/bin/env python2.7

import argparse
import os

from pyruntime import filesystem

# TODO: Confirm the game is owned by steam?
# TODO: Option to clean install and redownload?
# TODO: Option to download through Wine Steam?

parser = argparse.ArgumentParser()
parser.add_argument("appid", help="the application's id to download")
args = parser.parse_args()
appid = args.appid

if appid <= 0:
  print "Invalid appid of {}!".format(appid)
  exit(1)

filename = filesystem.STEAM_ROOT + "/SteamApps/appmanifest_{}.acf".format(appid)

if os.path.isfile(filename):
  print "{} already has an appmanifest!".format(appid)
  exit(1)

f = open(filename, 'w')
f.write('"AppState"\n')
f.write('{\n"')
f.write('\t"AppID"\t"{}"\n'.format(appid))
f.write('\t"Universe"\t"1"\n')
f.write('\t"StateFlags"\t"1026"\n')
# StateFlags 1026 means 'Updated Started', if my sources are correct
f.write('}\n')
f.close()

print "Done.  Restart Steam to begin the download."

