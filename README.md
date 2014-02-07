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

## A few words of warning

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

Unknown Steam DLLs?  That's a paddlin'.  Non-VAC games should be safe.

## Enough of all that, down the rabbit hole

The short version:

### Compiling the Windows Proxy DLL

Proxy needs Windows with Visual Studio, and has a Solution in
proxy/steam-proxy-win32.

### Compiling the Linux Bridge Library

Bridge needs a Linux install that can compile 32-bit binaries.  You'll
need g++, make, Wine & its development headers, and 32-bit libconfig &
its development headers.  A Makefile exists inside the winelib directory.

Deploy steam\_api\_bridge.dll.so to the 32-bit Winelib DLL folder.

### Alright, let's play

1. Download a game through Steam inside of Wine
2. Backup the game's *steam\_api.dll*
3. Copy *steam\_api\_proxy.dll* in place of *steam\_api.dll*
4. Party wildly
5. Pause partying and review COMPILE.md for the full notes
6. Run the game using Wine
7. Continue partying

## What SteamBridge works with

Defcon!  And Defcon's demo!

