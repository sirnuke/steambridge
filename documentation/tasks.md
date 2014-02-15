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
* Add configured Windows games as Steam shortcuts automagically (it can
  be done!)
* Consolidate paths/versions/etc to a single file.  Right now, the
  location of SteamBridge deployment is hardcoded in various places.
* Rename various references from 'games' to 'applications'.  More
  technically accurate, which is the best kind of correct.
