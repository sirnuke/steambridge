# Upcoming (0.0.2) Structure

* $PREFIX/bin
  * $PREFIX/bin/steambridge - Main client program, runs as a GUI by
    default.  Written in Python and uses GTK2 (GTK3?) via magic python
    bindings.  Also takes a set of 'commands' to manually execute actions
    from the commandline.
* $PREFIX/share/steambridge
  * pyruntime/ - Various internal Python code for SteamBridge
  * libsteam\_api.so - Copy of Valve's SteamWorks API that is distributed
    with SteamBridge.
  * steam\_api\_proxy.dll - Visual Studio compiled copy of the proxy DLL.
  * steam\_api\_bridge.dll.so - Winelib bridge library.
* $HOME/.steam/root/SteamBridge
  * $HOME/.steam/root/SteamBridge/appdb - Contains directories of
    configuration data on local Steam Applications.
  * $HOME/.steam/root/SteamBridge/wineprefixes - Root directory of
    SteamBridge managed Wine instances.
  * $HOME/.steam/root/SteamBridge/downloaded - Stores files downloaded
    from the interwebs.  Notably, Visual C++ runtime and a copy of the Steam client.

## Notes

* Support $PREFIX and $HOME/.steam/root/SteamBridge being the same.  The
  user's SteamBridge directory should be override-able by an environmental
  setting as well.
* Do NOT copy any libraries to public Linux directories.
  Copying libsteam\_api.so somewhere is just asking for trouble.
  steam\_api\_bridge.dll.so might be fine, but better to play everything
  safe (especially if the user is using a custom Wine setup).


