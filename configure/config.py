#!/usr/bin/env python2.7
# config.py - Generates configuration files for the C/C++ and Python code.
# Copyright (c) 2014 Bryan DeGrendel
#
# See COPYING and license/LICENSE.steambridge for license information

import utilities

options = utilities.Options()

# TODO: Check arguments here
# TODO: Check environmental variables here

options.save()

config = options.configure()

config_header = open('common/include/config.h', 'w')
config_header.write("""#ifndef ___STEAM_BRIDGE_CONFIG_H___
#define ___STEAM_BRIDGE_CONFIG_H___

// NOTICE: This file is automatically generated by make config.
//         See installation/settings.py for instructions on how to
//         modify it.

#define _STEAM_BRIDGE_APPNAME "{steambridge[app_name]}"
#define _STEAM_BRIDGE_WEBPAGE "{steambridge[webpage]}"

#define _STEAM_BRIDGE_VERSION_MAJOR {steambridge[version][major]}
#define _STEAM_BRIDGE_VERSION_MINOR {steambridge[version][minor]}
#define _STEAM_BRIDGE_VERSION_PATCH {steambridge[version][patch]}

#define _STEAM_BRIDGE_VERSION_SHORT "{steambridge[version][short]}"
#define _STEAM_BRIDGE_VERSION_LONG "{steambridge[version][long]}"

#define _STEAM_BRIDGE_LOCAL "{steambridge[local][root]}"
#define _STEAM_BRIDGE_CONFIG "{steambridge[local][config]}"
#define _STEAM_BRIDGE_APPDB_ROOT "{steambridge[local][appdb]}"
#define _STEAM_BRIDGE_APPDB_CONFIG "{steambridge[local][appdb_config_filename]}"

#define _STEAM_BRIDGE_API_LIB "{steambridge[prefix][steam_api_lib]}"

#endif //___STEAM_BRIDGE_CONFIG_H___
""".format(**config))
config_header.close()

python_config = open('interface/pysteambridge/config.py', 'w')
python_config.write("""# NOTICE: This file is automatically generated by make config.
#         See common/settings.py for instructions on how to modify it.

# Root directory of the local steam installation
STEAM_ROOT="{steam[root]}"

# Location of appmanifest_*.acf files
STEAM_APPMANIFESTS="{steam[app_manifests]}"

# Common root of installed Steam games
STEAM_APPS="{steam[apps]}"

# Root directory of the user's SteamBridge deployment
STEAM_BRIDGE_LOCAL="{steambridge[local][root]}"

# Configuration filename, used by the C++ library
CONFIG_FILENAME="{steambridge[local][config]}"

# Root directory of the SteamBridge installation
STEAM_BRIDGE_PREFIX="{steambridge[prefix][root]}"

# Location of the Win32 native steam_api proxy DLL
# This is the location when it's deployed
PROXY_DLL="{steambridge[prefix][proxy_dll]}"

# Location of the Winelib bridge library
BRIDGE_LIB="{steambridge[prefix][bridge_lib]}"

# Location of Winelib DLL, used as WINEDLLPATH
WINEDLLPATH="{steambridge[prefix][winedllpath]}"

# Location of the native Linux steam_api library
STEAM_API_LIB="{steambridge[prefix][steam_api_lib]}"

# Root directory of the internal AppDB
APPDB_ROOT="{steambridge[local][appdb]}"

# AppDB configuration filename
APPDB_CONFIG="{steambridge[local][appdb_config_filename]}"

# Directory storing the main steambridge client script
BIN_DIR="{steambridge[prefix][bin]}"

# Directory storing the Python Runtime library
PYSTEAMBRIDGE_DIR="{steambridge[prefix][pysteambridge]}"

# The official, formal name of the library
APP_NAME="{steambridge[app_name]}"

# The formal copyright statement
COPYRIGHT="{steambridge[copyright]}"

# Version string information
VERSION_MAJOR={steambridge[version][major]}
VERSION_MINOR={steambridge[version][minor]}
VERSION_PATCH={steambridge[version][patch]}

VERSION_SHORT="{steambridge[version][short]}"
VERSION_LONG="{steambridge[version][long]}"
""".format(**config))
python_config.close()
