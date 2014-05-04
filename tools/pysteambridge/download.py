# download.py - API for downloading an application
# Copyright (c) 2014 Bryan DeGrendel
#
# See COPYING and license/LICENSE.steambridge for license information

import appmanifest, config

# TODO: Confirm the game is owned by steam?
# TODO: Option to clean install and redownload?
# TODO: Option to download through Wine Steam?

class DownloadException:
  def __init__(self, message):
    self._message = message

  def __str__(self):
    return self._message

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

