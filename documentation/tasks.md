# Open Tasks

In no particular order, general things that need to be done:

* Various places (bridge/state, notably) need some polishing.
* Investigate how to compile the Proxy using MinGW.  I'm fairly sure it
  can be done.  I'm more sure that it won't be easy.
* Write a decoder for appcache/appinfo.vdf.  appinfo stores information
  related to the executable and icon.
* Better determine whether 'weird' variable types are handled by the
  Proxy assembler correctly.
* Write a GUI to handle downloading/configuring/etc of applications.
* Add configured applications as Steam shortcuts automagically (it can
  be done!)
* Handle WINEPREFIXESes.  Right now everything just uses the default one.
  It may be nice to have everything in it's own PREFIX.
* Download applications through Wine, and automagically transfer them to
  Linux Steam.
* vcrun2010, and friends.  Should be done with some degree automation
  through SteamBridge, I think.
* It'd be nice to compare version string information between the Proxy
  and Bridge, and warn if they don't reasonably match.

