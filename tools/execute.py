#!/usr/bin/env python2.7

import argparse

parser = argparse.ArgumentParser()
parser.add_argument("appid", help="run this Steam game using Wine")
args = parser.parse_args()
appid = args.appid

print "TODO: Prepare and execute ({})".format(appid)

# Read internal configuration of `appid`
# Make sure prepare has worked correctly
# Enter the 'working' directory of `appid`
# Copy the proxy dll to steam_api.dll
# If steam_appid.txt exists and differs in expected value, back it up
# Write out steam_appid.txt containing `appid`
# Execute using WINEDEBUG="..." WINEPREFIX="..." WINEDLLPATH="..." wine app 2>... >...
