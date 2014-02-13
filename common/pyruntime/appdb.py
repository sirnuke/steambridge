# appdb.py - Wraps around an internal appdb state

import os

import filesystem

def cd_into(appid):
  # TODO: Handle this better?
  try:
    os.chdir(filesystem.APPDB_ROOT)
    os.mkdirs(appid)
    os.chdir(appid)
  except OSError as exception:
    print "Unable to make or cd into {}'s appdb directory: ({}) {}" \
        .format(appid, exception.errno, exception.strerror)
    exit(1)



