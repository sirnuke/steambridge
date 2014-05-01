#!/usr/bin/env python2.7

import appmanifest, config

# TODO: Confirm the game is owned by steam?
# TODO: Option to clean install and redownload?
# TODO: Option to download through Wine Steam?

class DownloadException:
  def __init__(self, message):
    self._message = message

  def __str__(self):
    return self._message

def help():
  print '{} download: --appid APPID'.format(config.APP_NAME)
  exit(0)

def error(message):
  print '{} download: {}'.format(config.APP_NAME, message)
  exit(1)

def cli(args):
  appid = None
  i = 0
  while i < len(args):
    arg = args[i].lower()
    if arg == '--help' or arg == '-h':
      help()
    elif arg == '--appid':
      if i + 1 >= len(args):
        error('--appid is missing argument')
      try:
        appid = int(args[i + 1])
      except ValueError:
        error("Invalid appid '{}'".format(args[i + 1]))
      i += 1
    else:
      if len(arg) >= 2 and arg[0:2] == '--':
        error("Unknown flag '{}'".format(args[i]))
      else:
        error("Unknown or unexpected argument '{}'".format(args[i]))
    i += 1
  if appid == None:
    error('Missing appid')

  try:
    do(appid)
  except DownloadException, e:
    error(e)
  print "Download of {} configured, restart Steam to begin".format(appid)

# appid must be an int
def do(appid):
  manifest = appmanifest.AppManifest(appid)

  if manifest.exists():
    raise DownloadException("{} already has a manifest!".format(appid))

  with open(manifest.filename(), 'w') as f:
    f.write('"AppState"\n')
    f.write('{\n"')
    f.write('\t"AppID"\t"{}"\n'.format(manifest.appid()))
    f.write('\t"Universe"\t"1"\n')
    f.write('\t"StateFlags"\t"1026"\n')
    # StateFlags 1026 means 'Updated Started', if my sources are correct
    f.write('}\n')

