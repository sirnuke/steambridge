# Open Tasks

In no particular order, general things that need to be done:

* Various places (bridge/state, notably) need some polishing.
* Likely common API calls should be implemented.
* Investigate whether the Proxy can be compiled using MinGW.
* Write a decoder for appcache/appinfo.vdf.  appinfo stores information
  related to the executable and icon.
* Determine whether via inline assembler you can directly call Linux
  virtual functions inside of a Win32 Visual Studio DLL.  90% sure this
  is possible, though also 90% sure it might not be worth the effort.
  It would allow Bridge to be a very simple library wrapping around a
  handful of C API calls, rather than all C/C++ API calls as it stands
  right now.
* Write a GUI to handle downloading/configuring/etc of applications.
* Add configured applications as Steam shortcuts automagically (it can
  be done!)
* Handle WINEPREFIXESes.  Right now everything just uses the default one.
  It may be nice to have everything in it's own PREFIX.
* Download applications through Wine, and automagically transfer them to
  Linux Steam.
* vcrun2010, and friends.  Should be done with some degree automation
  through SteamBridge, I think.
* SteamBridge's bridge API as a pure C library?  It shouldn't be that bad
  to wrap the Wine stuff such that it can be compiled and used stand
  alone.
* It'd be nice to compare version string information between the Proxy
  and Bridge, and warn if they don't reasonably match.

