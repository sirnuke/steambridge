#!/usr/bin/env python2.7
# steambridge.py - Tool for interacting with a SteamBridge installation
# Copyright (c) 2014 Bryan DeGrendel
#
# See COPYING and license/LICENSE.steambridge for license information

import argparse, sys, os

# This string is replaced by the installation script to be the root
# directory of the shared directory
SHARED_DIRECTORY = "$SHARED$"
APP_NAME="steambridge"

sys.path.append(os.path.join(os.path.dirname(__file__), SHARED_DIRECTORY))

def error(message):
  print "{}: {}".format(APP_NAME, message)
  exit(1)

try:
  from pysteambridge import filesystem
except Exception as e:
  error(e)
  exit(1)

try:
  from pysteambridge import config
  from pysteambridge import download, execute, setup
  APP_NAME = config.APP_NAME
except filesystem.FilesystemException, e:
  error(e)
  exit(1)

def help():
  print "USAGE: {} command [arguments]".format(APP_NAME)
  print
  print "Where command is one of the following:"
  print "  download     Download an application"
  print "  setup        Setup a downloaded application"
  print "  execute      Run an application"
  print
  exit(0)

class CLI:
  def download(self, args):
    parser = argparse.ArgumentParser(prog='{} download'.format(config.APP_NAME))
    parser.add_argument('appid', type=int, help='the AppID to download')
    args = parser.parse_args(args)
    download.do(args.appid)

  def setup(self, args):
    parser = argparse.ArgumentParser(prog='{} setup'.format(config.APP_NAME))
    parser.add_argument('appid', type=int, help='the AppID to setup')
    args = parser.parse_args(args)
    setup.do(args.appid)

  def execute(self, args):
    parser = argparse.ArgumentParser(prog='{} execute'.format(config.APP_NAME))
    parser.add_argument('appid', type=int, help='the AppID to execute')
    args = parser.parse_args(args)
    execute.do(args.appid)

if len(sys.argv) < 2:
  # TODO: This will mean GUI, in the future
  error('Need a command')

cmd = sys.argv[1].lower()
cli = CLI()

if cmd == '--help' or cmd == '-h' or cmd == 'help':
  help()
elif cmd == 'download':
  cli.download(sys.argv[2:])
elif cmd == 'setup':
  cli.setup(sys.argv[2:])
elif cmd == 'execute':
  cli.execute(sys.argv[2:])
else:
  if len(cmd) >= 2 and cmd[0:2] == '--':
    error("Unexpected flag '{}', expected --help or command".format(sys.argv[1]))
  else:
    error("Unknown command '{}'".format(sys.argv[1]))

