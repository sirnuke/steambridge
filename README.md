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
Wine and the Linux-native Steam client.

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

But I won't use SteamBridge with an account of importance.  I understand
Valve has the ability, and potentially the cause, to swing the banhammer.

### Will this net me a VAC ban?

Unknown Steam DLLs?  That's a paddlin'.  Non-VAC games should be safe.

## Enough of all that, down the rabbit hole

### Compiling the Windows Proxy DLL

Proxy needs a Windows environment with Visual Studio.

### Compiling the Linux Bridge Library

Bridge needs a Linux environment that can compile 32-bit binaries.
You'll need g++, make, Wine & its development headers, and 32-bit
libconfig & its development headers.  The root Makefile compiles the
library, and setups the SteamBridge data directory.

### Alright, let's play

1. Download a game through Steam inside of Wine
2. Backup the game's *steam_api.dll*
3. Compile *steam_api_proxy.dll* using Visual Studio
4. Copy *steam_api_proxy.dll* in place of *steam_api.dll*
5. If it doesn't exist, create *steam_appid.txt* containing the AppId
and no newline
6. Compile *steam_api_bridge.dll.so* with **make**
7. Setup the SteamBridge environment with **make install** (no sudo!)
8. Run the main executable in Wine
6. Party wildly

Review *documentation/indepth.md* for the full notes

## What SteamBridge works with

Defcon!  And Defcon's demo! (1520/1522)   And Ethan Meteor Hunter's
demo! (273280)

## And from here into oblivion

It takes some persuasion, but Steam games in Wine can be run directly
through the Linux client.  This even gives you a hobbled version of
the Overlay.

Additionally, it's possible to force the Linux client to download many
games from a user's library that don't have a Linux port.

Combined, the long term goal is a tool to download Windows games,
configure them to run using the SteamBridge DLLs, and do most of the
work of adding it back to the client as a non-Steam game.

