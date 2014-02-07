Overview
================

SteamBridge lets you run (some) Steam games on Linux using Wine, but
through the native Steam client.  Long term, it will allow non-Windows
users access to their Windows library without the burden of switching
Steam clients.

***AND***

SteamBridge is cover for a secret government investigation into the
calling conventions on Windows and Linux.  The reports are classified;
rumored to complain about unnecessary differences between the two
Operating Systems, and how masochism isn't covered by Work's Comp.

***AND***

SteamBridge is a forbidden love story between two star-crossed lovers.
Windows-only Steam games running in Wine, but residing side-by-side with
their Linux Steam Client and games brethren?  It was a romance almost too
scandalizing to even speak of, but will Steam's powerful father object?

But What Is It, Really?
================

SteamBridge is a recreation of the SteamWorks API DLL (Steam\_api.dll)
that acts a simple proxy between Wine and a Linux-native libsteam\_api.so.
It exists in two intertwined forms:

A Winelib Linux-native Bridge Library
----------------

steam\_api\_bridge.dll.so is compiled as a native Linux DLL that offers
a C API that wraps pretty thinly over all the functionality provided
by libsteam\_api.so.  In particular, it offers a clean C API to all the
blackmagic C++ stuff Valve has done beyond their thin, public API.

It could, conceivably, be the basis for a Linux C API into the world of
Steamworks, though that's not the intention.

There's also a Visual Studio 2010 project that implements the same C API,
so the Proxy Windows DLL has something to link against.

A Win32 Proxy DLL replacing Steam\_api.dll
----------------

Compiled through Visual Studio 2010, this acts a fairly thin wrapper for
the functionality provided by the real Steam\_api.dll.  In particular,
all the C++ stuff that happens behind the scene.  This DLL is only really
useful inside a Wine environment.

Will All This Get Me Banned?
================

I don't know!  It might!  It arguably breaks the letter of the Steam
Subscriber Agreement, though in my opinion, not the intent.  It won't
let you play games that you don't own, for example.

I would describe Valve like a deity of an Abrahamic religion.  All
powerful; all knowing, and yet unknowable.  It might rain gifts of free
games down upon you.  It might smite you for not properly sacrificing
your goats - and as you lay dying, you'll wonder "...what goats?"

Until Valve comes down and clarifies in one way or another, don't use
this with an important account.  In fact, I highly recommend taking the
following pledge:

The SteamBridge User Pledge
----------------

*Raise your right hand and repeat after me*

I, [state your name], have done many stupid things before, perhaps on the magnitude of:

* Eyeballing a cut on a critical piece of wood.
* Buying a used car without even turning it on.
* Telling a significant other that what they are upset about "isn't a big deal."
* And while clarifying, insinuating that they are also fat.
* Buying a game at full price purely from the box art.
* Taking a payday loan, because, hey, it's free money, right?

But I will never be so stupid as to use SteamBridge with an account of
any importance.  SteamBridge makes no effort to hide itself.  I fully
understand Valve has the ability, and possibly the cause, to swing
the banhammer.

*Lower right hand*

Will This Net Me a VAC Ban?
================

Unknown DLLs being loaded?  Dohhhhhh, that's a paddling.

Not that SteamBridge is anywhere near being able to run any VAC-enabled
games.  If, and when, that time comes, it's unlikely that you don't
receive at least a VAC-kick.

SteamBridge, however, should not affect VAC status of non-VAC games.
I'm not personally aware of any bans occurring outside from outside their
respective games, with the semi-exception of the Golden Wrench fiasco.

How Do I Use SteamBridge?
================

*Mysterious empty section!*

How Does It Actually Work?
================

*Mysterious empty section!*


