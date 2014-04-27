# utilities.py - Utility code shared between various configuration and installation scripts
# Copyright (c) 2014 Bryan DeGrendel
#
# See COPYING and license/LICENSE.steambridge for license information

def directories(prefix = None, local = None, steam_root = None):
    if not steam_root:
        steam_root = '.steam/root'
    if not prefix:
        prefix = '/usr/local'
    if not local:
        local = steam_root + '/SteamBridge'
    shared = prefix + '/share/steambridge'
    doc = prefix + '/share/doc/steambridge'

    return  {
                'steam': {
                    'root': steam_root,
                    'app_manifests': steam_root + '/SteamApps',
                    'apps': steam_root + '/SteamApps/common',
                },
                'steambridge': {
                    'local': {
                        'root': local,
                        'config': local + '/configuration.json',
                        'appdb': local + '/appdb',
                        'appdb_config_filename': 'appdb.json',
                    },
                    'prefix': {
                        'root': prefix,
                        'shared': shared,
                        'winelib_path': shared,
                        'bridge_lib': shared + '/steam_api_bridge.dll.so',
                        'steam_api_lib': shared + '/libsteam_api.so',
                        'proxy_dll': shared + '/steam_api_proxy.dll',
                        'pysteambridge': shared + '/pysteambridge',
                        'bin': prefix + '/bin',
                    },
                },
            }


def settings():
    version_major = 0
    version_minor = 0
    version_patch = 2
    return  {
                'app_name': 'SteamBridge',
                'copyright': 'Bryan DeGrendel (c) 2014',
                'license': 'See license directory for full information',
                'webpage': 'https://github.com/sirnuke/steambridge',
                'version': {
                    'major': version_major,
                    'minor': version_minor,
                    'patch': version_patch,
                    'short': '{}.{}.{}'.format(version_major, version_minor, version_patch),
                },
            }

