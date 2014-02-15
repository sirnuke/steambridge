# The short version

1. Compile the Visual Studio solution (Release build).  Copy
*steam_api_proxy.dll* to the Linux tree.
2. Install g++ & multilib and a recent version of Wine & dev.
3. Compile the Winelib DLL using the provided *Makefile*.
4. Setup the SteamBridge environment with **make deploy** (no root/sudo).
Various tools are installed to *~/.steam/root/SteamBridge/bin*.
5. Download an application using *download.py*.  Various applications
won't download correctly.  You'll need to use the Windows native
Steam client (probably inside Wine).  Copy the appmanifest file in
*SteamApps* and the installation directory in *SteamApps/common* to
*~/.steam/root/SteamApps/* manually.  Eventually, this will be handled
through SteamBridge.
6. Configure the game using *configure.py*.
7. Execute the game using the newly created .desktop file or *execute.py*.

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

To compile, run **make** from the root.  All, clean, rebuild, deploy, and
redeploy are implemented.  Deploy sets up the SteamBridge environment
inside your home directory.  Redeploy deletes the existing one and
then deploys.  As everything is contained within your home, root/sudo
access is not needed.

*steam_api_bridge.dll.so* is the compiled binary, a Winelib
library for use with Wine.  The SteamBridge deployment copies it to
*~/.steam/root/SteamBridge/*.  Execute sets up the Wine settings to look
there for WineLib DLLs.

# Deployment and execution notes

* You need *steam_appid.txt* in the same folder as *steam_api.dll*,
  containing the appid with no newline.  **echo -n "1520" >
  steam\_appid.txt**, for example.  Applications that have the file
  already, but set to an unexpected value, will break SteamBridge.
* Output is stored in ~/.steam/root/SteamBridge/appdb/[appid]/\*.txt.
* The built-in WINE Visual C+++ Runtime (2010, aka msvcp100.dll) works
  fine, outside a single specific scenario (so far).
* You can run Wine Steam games through Steam Linux using Steam's "Add
  Non-Steam Game..." feature.  See the .desktop file created by Configure.
    * In my test setup, the built-in msvcp100.dll blows up inside its
      DllMain, possibly due to issues with establishing stdin/stdout.
      Installing the real DLL (winetricks vcrun2010) works right.
    * The Steam overlay loads (!) and opens/closes correctly (!), but
      doesn't capture the mouse correctly (so close).
    * Furthermore, Steam API calls impact the injected Overlay.
      Ethan: Meteor Hunter sets the corner of popups, and the Overlay
      obeys.  This is a bit of an unexpected surprise.
    * The content of the Overlay isn't tied to the real game.  It's
      still the generic links and content.
* Gametime is properly recorded!
* *libsteam_api.so* is forward compatible, so long as newer APIs aren't
  used (which will crash, hopefully quickly).  The Source 1 SDK is behind
  the library used in Ethan Meteor Hunter, but it appears to run fine.
  My guess is as long as the game doesn't use any new API calls, the
  older library will work fine.

