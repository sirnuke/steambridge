# SteamBridge

## What is SteamBridge?

SteamBridge is a forbidden love story between two star-crossed lovers.
Windows Steam applications running in Wine, but residing side-by-side
with their native Steam brethren?  It's an affair too scandalizing to
even speak of in public.  But will Steam's powerful father object?

### AND

SteamBridge is a cover for a secret government investigation into the
calling conventions on Windows and Linux.  The reports are classified;
rumored to contain fierce arguments about how to return values, and
complaints that masochism isn't covered by Work's Comp.

### AND

SteamBridge lets you run Steam applications on Linux using Wine, but
while still using the native Steam client.  The long term goal is to allow
Linux users access to their Windows library without switching clients.

More technically, SteamBridge is primarly a two part recreation of
the Steam API DLL that acts a proxy between Wine and the Linux-native
Steam client.

## A few words of warning

### Will using SteamBridge get me banned?

Don't know!  It arguably breaks the letter of the Steam Subscriber
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
You'll need g++ & friends, plus Wine & its development headers.
The root Makefile compiles the library, and deploys SteamBridge with
**make deploy**.

Once deployed, various helpful tools exist in
~/.steam/root/SteamBridge/bin.  *download.py* will configure Linux Steam
to download a Windows application, *configure.py* configures it for
use with SteamBridge, and *execute.py* will run it.  All three take a
single parameter, the application's appid.  Note that Configure creates
a .desktop link on your desktop that runs the application.

### Alright, let's play

1. Download a game through Steam inside of Wine
2. Backup the game's *steam_api.dll*
3. Compile *steam_api_proxy.dll* using Visual Studio
4. Copy *steam_api_proxy.dll* to the Linux source
6. Compile *steam_api_bridge.dll.so* with **make**
7. Setup the SteamBridge environment with **make deploy** (no sudo!)
8. Enter ~/.steam/root/SteamBridge/root/
9. Download a game using *download.py*
10. Configure said game (when finished downloading!) with *configure.py*
11. Run the game using *execute.py*, or the newly created link on
your desktop
12. Party wildly

Review the *documentation* directory for more notes

## And from here into oblivion

Rather than local Python scripts, the end goal is to create a GUI that
handles downloading and configuring Windows games, including automagically
adding them as non-Steam shortcuts.

