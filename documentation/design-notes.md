# Design notes

* Why two DLLs?  The real *steam_api.dll* only offers a handful of
  API calls.  The meat is accessed through pointers to C++ class instances
  (ISteamUser, for example), and the real API is calling virtual functions
  in these classes.  This is a sneaky way to offer a complex API while
  retaining a straight forward backwards/forwards compatibility, but
  is a straight no-go with Winelib.  GCC and Visual Studio implement
  vastly different thiscalls, and the arguments are completely botched.
  As the C++ calls aren't a public API (no symbols), you can't reimplement
  them through Winelib.  Therefore, Proxy exists as an entirely Windows
  CLL that implements the C++ code, and makes the corresponding C calls
  to the Winelib Bridge.
* For development/tinkering, I've found valgrind, gdb, and [Dependency
  Walker](http://www.dependencywalker.com/) to be most helpful.
* Proxy and Bridge are mostly independent of each other.  Proxy only
  needs to be rebuild when the Bridge API changes.  Changes to the guts
  of Bridge do not affect Proxy.
* Re-run the winemaker.sh script when creating new Bridge source files
  to update the Makefile.
* Callbacks are bit of a tricky task.  Winelib cannot directly link
  to Win32 code.  At the moment, Proxy wraps around them, offering pure
  C functions.  Bridge takes advantage of the C calling convention
  being sufficiently similar on Windows and Linux, and calls the Win32
  code in Proxy as if it were a pointer to a Linux function.  This is
  hilariously brittle, but appears to work fine in practice.  Long term,
  it may be possible to manually load functions from the Proxy DLL using
  normal Win32 API calls - which are offered via Winelib.
