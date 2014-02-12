# The short version

1. Compile the Visual Studio solution (Release build).  Save the
*steam_api_proxy.dll* for later.
2. Install g++ & multilib, a recent version of Wine & development package,
and libconfig 32-bit library & development package.
3. Compile the Winelib DLL using the provided *Makefile*.
4. Setup the SteamBridge environment with **make install** (do not use
with sudo, it runs sudo for the one copy command that needs it).
5. Download a game through Steam running Wine.
6. Copy *steam_api_proxy.dll* in place of the game's *steam_api.dll*.
7. Setup *steam_appid.txt* with the game's appid, if not already set.
Needs to be the integer id and no newline.
8. With the Linux Steam client running, run the game using Wine.

# Windows Proxy DLL

The compilation spits out two DLLs: *steam_api_bridge.dll* and
*steam_api_proxy.dll*.  Bridge is a simple stub library that merely
implements the same API/symbols as the Linux Winelib library, necessary
for Proxy to have something to link against.

Proxy is a drop-in replacement for *steam_api.dll*.  Instead of
communicating with the Windows Steam client inside Wine, it communicates
with the Winelib Bridge. The Winelib Bridge, in turn, routes the API
calls to the native Linux Steam client.

# Linux Bridge Winelib library

To compile, run **make** from the root.  All, clean, rebuild, install,
and update tasks are implemented.  Install installs a fresh SteamBridge
directory (inside your home directory).  Update, however, doesn't
overwrite your existing configuration.  Don't run either with sudo, the
one action that requires root access is wrapped in sudo.  Additionally,
in the future everything will be stored within your home directory.

*steam_api_bridge.dll.so* is the compiled binary, a Winelib library
for use with Wine.  It needs to be deployed to the 32-bit Wine DLL
directory, likely */usr/lib/i386-linux-gnu/wine*.  Additionally,
SteamBridge depends on a directory within the user's local steam root
(~/.steam/root).  At the moment, this directory contains the SteamBridge
runtime settings, the upcoming database of appid SteamAPI versions,
and a copy of *libsteam_api.so*.  The included script *setup.sh* (make
install) will copy everything to the correct place, though it may be
brittle on non-standard directories.

# Deployment and execution notes

* Wine Steam might overwrite the SteamBridge Proxy DLL with the real
  *steam_api.dll*
* You need *steam_appid.txt* in the same folder as *steam_api.dll*,
  containing the appid with no newline.  **echo -n "1520" >
  steam\_appid.txt**, for example.  Many games have this already.
* Recommend wine debug settings of WINEDEBUG="+steam\_bridge" when
  running Wine games using SteamBridge.
* Long term, setting up *steam_api.dll* and *steam_appid.txt* will be
  handled by SteamBridge.
* Proxy outputs on stdout, and the Winelib Bridge DLL outputs on stderr.
  They step on each other's toes when both using stderr.
* Additionally, I recommend piping stdout and stderr, so you have a
  record if/when stuff breaks.
* Renaming the real *steam_api.dll* to *steam_api_original.dll* is a
  Good Idea, and lets you symlink to which ever one is currently being used.
* The built-in WINE Visual C+++ Runtime (2010, aka msvcp100.dll) works
  fine, outside a single specific scenario (so far).
* You can run Wine Steam games through Steam Linux using Steam's "Add
  Non-Steam Game..." feature.  You'll need a valid .desktop file,
  pointing to a script in $PATH that properly executes the game.
    * In my test setup, the built-in msvcp100.dll blows up inside its
      DllMain, possibly due to issues with establishing stdin/stdout.
      Installing the real DLL (winetricks vcrun2010) works right.
    * The Steam overlay loads (!) and opens/closes correctly (!), but
      doesn't capture the mouse correctly (so close).
    * Furthermore, Steam API calls impact the injected Overlay.
      Ethan Meteor Hunter sets the corner of popups, and the Overlay
      obeys.  This is a bit of an unexpected surprise.
    * The content of the Overlay isn't tied to the real game.  It's
      still the generic links and content.
* Gametime is properly recorded!
* *libsteam_api.so* is forward compatible, so long as newer APIs aren't
  used (which will crash, hopefully quickly).  The Source 1 SDK is behind
  the library used in Ethan Meteor Hunter, but it appears to run fine.
  My guess is as long as the game doesn't use any new API calls, the
  older library will work fine.

