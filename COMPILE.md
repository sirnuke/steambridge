# The short version

1. Compile the Visual Studio solution (Release build) in
*proxy/steam-proxy-win32*.  Save the generated *steam\_api\_proxy.dll*
for later.
2. Install g++ & multilib, a recent version of Wine & development package,
and libconfig 32-bit library & development package.
3. Compile the Linux Winelib DLL using **make** inside
*bridge/winelib/steam_api_bridge.dll/*.
4. Setup the SteamBridge environment using the *setup.sh* script.
5. Download a game through Steam running Wine.
6. Copy *steam\_api\_proxy.dll\* in place of the game's *steam\_api.dll\*.
7. Setup *steam\_appid.txt* with the game's appid, if not already set.
Needs to be the integer id and no newline.
8. With the Linux Steam client running, run the game using Wine.
9. Party wildly.

# Windows Proxy DLL

You'll need a Windows setup with Visual Studio installed.  I'm using
2010 Express on Windows 7 64-bit.  Other modern versions of Visual Studio
and Windows are probably fine.

Unfortunately, Visual Studio doesn't work inside of Wine.  There's also
enough fuzziness to C++ that it's unlikely MinGW will work without
considerable persuasion.  The Free Software dream of a Windows-less
future remains onhold.

I will note, for future reference, that GCC and Visual Studio do agree
on enough that it might be feasible to use MinGW, so long as we stay
away from pesky exceptions and the like.  For example, they seem to
implement virtual tables the same way.

I'm using Visual Studio 2010 because it's the latest version supported by
the Source 1 SDK, though that's not a requirement.  If you do use 2010,
install Service Pack 1.

A Visual Studio solution exists in proxy/steam-proxy-win32.  You'll need
to make a Release build, as Wine doesn't like Debug ones (specifically,
Wine lacks a corresponding a msvcrt\*d.dll).

The compilation spits out two DLLs: steam\_api\_bridge.dll and
steam\_api\_proxy.dll.  Bridge is a simple stub library that merely
implements the same API/symbols as the Linux Winelib library, necessary
for Proxy to have something to link against.

Proxy is a drop-in replacement for steam\_api.dll - and when deployed,
should be named steam\_api.dll.  Instead of communicating with the Steam
client running inside Wine, it communicates with the Winelib Bridge,
which in turn connects to the native Steam client.

# Linux Bridge Winelib library

You'll need an x86 Linux environment that can produce 32-bit binaries.
My test bed is a 13.10 64-bit Ubuntu install.

On a 64-bit Ubuntu installation, you'll (roughly) want *build-essential*,
*g++*, *g++-multilib*, *wine1.7*, *wine1.7-dev*, *libconfig9:i386*,
*libconfig9-dev*.  32-bit distros won't need *g++-multilib*, and
can substitute *libconfig9* for *libconfig9:i386*.  Other distros will
probably have similar requirements.

Note that libconfig9:i386 doesn't setup the *libconfig.so* library
symlink.  On my Ubuntu test machine, **cd /usr/lib/i386-linux-gnu/ ; sudo
ln -s libconfig.so.9 libconfig.so** does the trick. 

To compile, enter *bridge/winelib/steam\_api\_bridge.dll* and run
**make**.  Standard make commands are implemented, with the exception
of install.  Installation is handled by *setup.sh*, which eventually
will be called by **make install**.

*steam\_api\_bridge.dll.so* is the compiled binary, a Winelib library
for use with Wine.  It needs to be deployed to the 32-bit Wine DLL
directory, likely */usr/lib/i386-linux-gnu/wine*.  Additionally,
SteamBridge depends on a directory within the user's local steam root
(~/.steam/root).  At the moment, this directory contains the SteamBridge
runtime settings, the upcoming database of appid SteamAPI versions,
and a copy of *libsteam\_api.so*.  The included script *setup.sh*
will copy everything to its correct place, though it may be brittle on
non-standard directories.

# Deployment and execution notes

* Wine Steam might overwrite the SteamBridge Proxy DLL with the real
  *steam\_api.dll*
* You need *steam\_appid.txt* in the same folder as *steam\_api.dll\*,
  containing the appid with no newline.  **echo -n "1520" >
  steam\_appid.txt**, for example.  Many games have this already.
* Recommend wine debug settings of WINEDEBUG="+steam\_bridge" when
  running Wine games using SteamBridge.
* Proxy outputs on stdout, and the Winelib Bridge DLL outputs on stderr.
  They step on each other's toes when both using stderr.
* Additionally, I recommend piping stdout and stderr.
* Renaming the real *steam\_api.dll* to *steam\_api_original.dll* is a
  Good Idea, and lets you symlink to which ever one is currently being used.
* The built-in WINE Visual C+++ Runtime (2010, aka msvcp100.dll) works
  fine, outside seemingly a single specific scenario (so far).
* You can run Wine Steam games through Steam Linux using Steam's "Add
  Non-Steam Game..." feature.  You'll need a valid .desktop file,
  seemingly pointing to a script in $PATH that properly executes the
  game.
    * In my test setup, the built-in msvcp100.dll blows up inside its
      DllMain, possibly due to issues with establishing stdin/stdout.
      Installing the real DLL (winetricks vcrun2010) works right.
    * The Steam overlay loads (!) and opens/closes correctly (!), but
      doesn't capture the mouse correctly (so close).
    * Furthermore, Steam API calls from the client impact the injected
      Overlay - aka, Ethan Meteor Hunter sets the corner of popups,
      which is reflected.  This is a bit of an unexpected surprise.
    * The content of the Overlay isn't tied to the real game.  It's
      still the generic links and content.
* Gametime is properly recorded!

# Miscellaneous design notes

* Why two DLLs?  The real *steam\_api.dll* only offers a handful of
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

# Outstanding tasks

* Various parts of the code are ugly.
* Probably worth doing some of the more likely common API calls before
  finding apps that use them.
* It'll be a huge pain, but it'd be nice to shove the Visual Studio
  stuff into a better directory naming scheme.
* Investigate whether the Proxy can be compiled using MinGW.
* Root build script?
* More tools to help automate setting up apps to use SteamBridge.
* Definitely will need a better way to store API versions.  Sqlite is
  the knee-jerk reaction.

