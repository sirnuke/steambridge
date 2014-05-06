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

* Create a Gtk2 (Gtk3?) GUI for configuration games.

## 0.0.5

* Support automagically downloading games from Wine-Steam.  This definitely
  requires a lot of blood, sweat, and tears; unfortunately, but it'll
  be necessary for a lot of games to Just Work.

## 0.1.0

* More black magic assembler to support compiling using MinGW.
  Estimated timeline: heat death of the universe, or HL3's release date,
  whichever comes sooner.

# Open tasks

* Cleanup in various C++ code.  *bridge/state* is a notable location.
* More vigorous testing of whether assembly black magic works in all cases.
* Compare version data of Proxy and Bridge.  Warn if they don't match.
* Configure script doesn't take options, yet.  Also needs --help output.
  Might need to extract config from the Makefile, as make is an outdated
  tool that survives on shear momentum.
* configure/utilities.py generates different long version data each time
  it is run!
* Some files may still need license/info headers.

