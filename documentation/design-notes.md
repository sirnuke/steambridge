# Design notes

* Why two DLLs?  The real *steam_api.dll* only offers a handful of
  API calls.  The meat is accessed through pointers to C++ class instances
  (ISteamUser, for example), and the real API is calling virtual functions
  in these classes.  This is a sneaky way to offer a complex API while
  retaining a straight forward backwards/forwards compatibility, but
  is a straight no-go with Winelib.  GCC and Visual Studio implement
  subtly different thiscalls, notably with stack cleanup and passing
  this.  As the C++ calls aren't a public API (no symbols), you can't
  reimplement them through Winelib.  Therefore, Proxy exists as a pure
  Windows DLL that implements the C++ code.  It retrieves the actual C++
  object pointers from the Bridge library, and uses black magic assembler
  translates to and from GCCspeak.
* Converting from Steam headers to a Win32 C++ source is done by
  convert-steam-header.rb (in tools/).  It takes a single argument,
  the Steam header file, and generates a mostly correctly C++ source &
  header file for use in Visual C++.  Note that the original header will
  need to be tweaked a bit in some cases (isteamclient.h).  This automatic
  conversion handles the grunt work of wrapping around a GCC thiscall.
  It's only necessary to run this script when implementing an entirely
  new Steam class.
  * It requires modern version of Ruby, of course.  Ruby is not needed
    by anything else in SteamBridge.
  * The conversion script is pretty ugly. Expected ch-ch-ch-changes.
* GCC stores the pointer to a class's virtual table in the first 4
  (8 on 64-bit systems) bytes of the class.  Functions are the offset
  of where its defined in the header.  The first function is located
  in the first 4 (or 8) bytes of the vtable, the second is in vtable+4,
  and so on.
* GCC stores this as a hidden parameter (pushed last onto the stack),
  whereas Visual Studio passes it using ECX.  Amusingly, it seems Visual
  Studio almost always just pushes ECX to the stack early in functions
  anyway.
* Returning structs by value is a fairly involved endeavour, even when
  it's a well defined, set 64-bits (CSteamID).  GCC expects a hidden
  pointer pushed last (after this) of where to store the value.
  Despite otherwise being 100% caller stack cleanup, GCC functions
  will pop (!) this hidden pointer.  The value of the hidden pointer
  is returned in EAX, but who cares.
* Visual Studio 2010 seems to have a bug where it optimizes the local
  struct out of the function (using the same hidden struct passes by the
  caller), which isn't reflected in *lea <reg>, <local_storage_variable>*.
  It should load somewhere above the local stack (EBP+X), but instead
  tries to load a value in the local stack (EBP-X).  A work around is
  explicitly defining a local variable pointing to the result value (which
  is optimized correctly), and loading its value using a mov command.
* For development/tinkering, I've found valgrind, gdb, and [Dependency
  Walker](http://www.dependencywalker.com/) to be most helpful.
  OllyDbg is useful for sorting out assembler problems.
* Proxy and Bridge are mostly independent of each other.  Proxy only
  needs to be rebuild when the Bridge API changes.
* Re-run the winemaker.sh script when creating new Bridge source files
  to update the Makefile.
* Callbacks are bit of a tricky task.  Winelib cannot directly link
  to Win32 code.  At the moment, Proxy wraps around them, offering pure
  C functions for the bridge.  Bridge takes advantage of the C calling
  convention being sufficiently similar on Windows and Linux, and calls
  the Win32 code in Proxy as if it were a pointer to a Linux function.
  This is hilariously brittle, but appears to work fine in practice.
  Long term, it may be possible to manually load functions from the
  Proxy DLL using normal Win32 API calls (GetProcAddress) - which are
  offered via Winelib.
