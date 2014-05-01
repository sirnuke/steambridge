# __init__.py - pysteambridge module
# Copyright (c) 2014 Bryan DeGrendel
#
# See COPYING and license/LICENSE.steambridge for license information

import filesystem

if not filesystem.validate():
  exit(1)
