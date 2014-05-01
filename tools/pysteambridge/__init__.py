# __init__.py - pysteambridge module
# Copyright (c) 2014 Bryan DeGrendel
#
# See COPYING and license/LICENSE.steambridge for license information

import filesystem

try:
  filesystem.validate()
except FilesystemException, e:
  raise Exception(str(e))

