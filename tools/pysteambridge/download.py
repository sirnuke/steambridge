#!/usr/bin/env python2.7

import argparse

from pyruntime import appmanifest

# TODO: Confirm the game is owned by steam?
# TODO: Option to clean install and redownload?
# TODO: Option to download through Wine Steam?

parser = argparse.ArgumentParser()
parser.add_argument("appid", help="the application's id")
# parser.add_argument("--wine", help="download through Wine steam")
args = parser.parse_args()

manifest = appmanifest.AppManifest(int(args.appid))

if manifest.exists():
  print "{} already has a manifest!".format(manifest.appid())
  exit(1)

with open(manifest.filename(), 'w') as f:
  f.write('"AppState"\n')
  f.write('{\n"')
  f.write('\t"AppID"\t"{}"\n'.format(manifest.appid()))
  f.write('\t"Universe"\t"1"\n')
  f.write('\t"StateFlags"\t"1026"\n')
  # StateFlags 1026 means 'Updated Started', if my sources are correct
  f.write('}\n')

print "Done.  Restart Steam to begin the download."

