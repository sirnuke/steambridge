#!/usr/bin/env python2.7

import sys, os

SHARED_DIRECTORY = "$SHARED$"

sys.path.append(os.path.join(os.path.dirname(__file__), SHARED_DIRECTORY))

try:
  from pysteambridge import *
except Exception, e:
  print e
  exit(1)

