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

### Will using SteamBridge get my Steam account banned?

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

Proxy needs a Windows environment with Visual Studio.  Visual Studio
2010 Express is used for development, and is a good, safe, free choice.

### Compiling the Linux Bridge Library

Bridge needs a Linux environment that can compile 32-bit binaries.  You'll
also need the normal build tools, plus Wine & its development headers.

SteamBridge installs with a script to manage applications.  *steambridge
download* will configure Linux Steam to download a Windows application,
*steambridge setup* will setup it up once downloaded, and *steambridge
execute* will run it.

### Alright, let's play

#### Compilation

1. Configure with **configure**
  * Run with **configure --help** to see configurable options
2. Compile the Proxy DLL using Visual Studio
  * You'll need to copy libraries/common/include/config.h to Windows,
    and copy Release/steam\_api\_proxy.dll back to Linux
  * The Proxy DLL must be a Release build
3. Compile the Bridge DLL with **make**
4. Deploy SteamBridge with **make install**
  * As a change from the first release, SteamBridge now installs to the
    system by default, rather than just your home directory

#### Execution

1. Start downloading with **steambridge download (appid)**.
  * You will need to restart Steam.
2. Once finished downloading, run **steambridge setup (appid)**.
  * This should create a shortcut on your desktop.
  * Note that Steam doesn't import this shortcut correctly.  You'll need
    to manually add the appid as a parameter to **steambridge execute**.
3. Party wildly.

#### Notes

As of this release, many applications cannot be downloaded through
SteamBridge.  SteamPlay and applications using multiple appids seem
to be notable culprits.  You can also download an application through
Windows Steam running inside of Wine, and copy appmanifest\_XXXX.acf
and installation to their corresponding directories under
*~/.steam/root/SteamApps/*.

Regardless of how the application is downloaded, it appears the Windows
Steam client still needs to be installed in the Wine prefix used with
SteamBridge.  Further investigation is ongoing.

SteamBridge depends on the Visual C++ runtime.  Wine includes an
implementation of this runtime, which works correctly in most cases.
On my test machine, the real runtime is needed when running a SteamBridge
application through Steam.  The easiest way to get this is to download
*winetricks* and run **winetricks vcrunXXXX** where XXXX corresponds to
the version of Visual Studio.

Review the *documentation* directory for more detailed notes and
information about SteamBridge.

