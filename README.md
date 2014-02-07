# SteamBridge

## What is SteamBridge?

SteamBridge is a forbidden love story between two star-crossed lovers.
Windows Steam games running in Wine, but residing side-by-side with
their native Steam brethren?  It's an affair too scandalizing to even
speak of in public.  But will Steam's powerful father object?

### AND

SteamBridge is a cover for a secret government investigation into the
calling conventions on Windows and Linux.  The reports are classified;
rumored to contain fierce arguments about how to return values, and
complaints that masochism isn't covered by Work's Comp.

### AND

SteamBridge lets you run Steam games on Linux using Wine, but through
the native Steam client.  Long term, it will allow non-Windows users
access to their Windows library without the burden of switching clients.

It's a two part recreation of the Steam API DLL that acts a proxy between
Wine and the Linux-native library.

## But first, a few words of warning

### Will using SteamBridge get me banned?

I don't know!  It arguably breaks the letter of the Steam Subscriber
Agreement, though not the spirit.  Unless Valve clarifies, don't use
this with a real account.  I recommend taking the SteamBridge User pledge:

#### The SteamBridge User Pledge

I, *[state your name]*, have done many stupid things, such as:

* Buying a game at full price half way through December.
* Taking a payday loan, because, hey, it's free money, right?
* Purchasing a used car without driving it.
* Telling my significant other that what they are upset about "isn't a
  big deal."
* And while clarifying, insinuating that they are fat.

But I won't use SteamBridge with an account of importance.  I understand
Valve has the ability, and potentially the cause, to swing the banhammer.

### Will this net me a VAC ban?

Unknown Steam DLLs?  That's a paddling.  Non-VAC games should be safe.

## Enough of all that, down the rabbit hole

### Compiling the Windows Proxy DLL

Windows with Visual Studio.  I'm using 2010 Express on Windows 7 64-bit.

Open the Solution in proxy/steam-proxy-win32.  Compile a Release build.

### Compiling the Linux Bridge Library

x86 Linux that can compile 32-bit binaries.  You'll need g++, make, Wine &
its development headers, and 32-bit libconfig & its development headers.

On a 64-bit Ubuntu installation, you'll (roughly) want *build-essential*,
*g++*, *g++-multilib*, *wine1.7*, *wine1.7-dev*, *libconfig9:i386*,
*libconfig9-dev*.  32-bit distros won't need *g++-multilib*, and
can substitute *libconfig9* for *libconfig9:i386*.

Note that libconfig9:i386 doesn't setup the *libconfig.so* library
symlink.  On my Ubuntu test machine, **cd /usr/lib/i386-linux-gnu/ ; sudo
ln -s libconfig.so.9 libconfig.so** does the trick. 

Lastly, you'll need libsteam\_api.so somewhere it can be found.  A copy
of libsteam\_api.so from the public Source 1 SDK can be found in the
*steam* folder.  **sudo cp steam/libsteam\_api.so /usr/lib/i386-linux-gnu/
; sudo ldconfig**, for example.

***NOTE***: that this might break native Steam games.  In the future,
SteamBridge will use dlopen.  LD\_LIBRARY\_PATH is a work around.

To compile, enter bridge/winelib/steam\_api\_bridge.dll and run **make**.

## Let's get to playing

1. Download a game through Steam inside of Wine, and quit Wine Steam
2. Copy steam\_api\_bridge.dll.so to the 32-bit Wine DLL directory
   * Should be /usr/lib/i386-linux-gnu/wine/
3. Backup a copy of the game's *steam\_api.dll*
4. Copy *steam\_api\_proxy.dll* from Windows in place of *steam\_api.dll*
5. Set *steam\_appid.txt* in the same folder as *steam\_api.dll\*
   * Contains the appid with no newline. **echo -n "1520" > steam\_appid.txt**
6. Login to native Linux Steam
7. Run the game using Wine
8. Party wildly

## What SteamBridge works with

Defcon!  And Defcon's demo!  Appid of 1522 (demo), and 1520.

