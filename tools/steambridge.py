#!/usr/bin/env python2.7

import sys, os

SHARED_DIRECTORY = "$SHARED$"
APP_NAME="steambridge"

sys.path.append(os.path.join(os.path.dirname(__file__), SHARED_DIRECTORY))

def error(message):
  print "{}: {}".format(APP_NAME, message)
  exit(1)

try:
  from pysteambridge import config, filesystem
  from pysteambridge import download
  APP_NAME = config.APP_NAME
except filesystem.FilesystemException, e:
  error(e)
  exit(1)

def help():
  print "USAGE: {} command [arguments]".format(APP_NAME)
  exit(0)

if len(sys.argv) < 2:
  # TODO: This will mean GUI, in the future
  error("Requires a command")

cmd = sys.argv[1].lower()

if cmd == '--help' or cmd == '-h':
  help()
elif cmd == 'download':
  download.cli(sys.argv[2:])
else:
  if len(cmd) >= 2 and cmd[0:2] == '--':
    error("Unexpected flag '{}', expected --help or command".format(sys.argv[1]))
  else:
    error("Unknown command '{}'".format(sys.argv[1]))

