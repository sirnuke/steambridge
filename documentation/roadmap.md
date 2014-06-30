# Roadmap

## 0.0.2

* Convert to a not stupid deployed layout.  It's not overly difficult
  to be properly UNIXy.
* Combine client tools into a single steambridge script, with various
  actions as parameters.
* Finally mail letter of permission to Valve overlords begging for permission.

## 0.0.3

* Support automagically installing Visual Studio runtime and Windows
  Steam client.  Probably just package winetricks.
* Add shortcuts to Steam automagically.
* Decode appcache/appinfo.vdf to get executable and icons for games.

## 0.0.4

* Add support for downloading games using SteamCMD, which is a clean
  and mostly painless method for downloading games from the command line.

## 0.0.5

* Create a Gtk2 (Gtk3?) GUI for configuration games.

## 0.1.0

* More black magic assembler to support compiling using MinGW.
  Estimated timeline: heat death of the universe, or HL3's release date,
  whichever comes sooner.

# Open tasks

* Cleanup in various C++ code.  *bridge/state* is a notable location.
* More vigorous testing of whether assembly black magic works in all cases.
* Compare version data of Proxy and Bridge.  Warn if they don't match.
* configure/utilities.py generates different long version data each time
  it is run!
* Some files may still need license/info headers.
* Remove Windows dependency on generated common header.
* OS X support!  Someday!
* Test SteamBridge on SteamOS.

