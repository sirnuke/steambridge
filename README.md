SteamBridge Overview
===========

This project is a recreation of the SteamWorks API DLL (steam\_api.dll) to allow Steam applications running under Wine to communicate with the native Linux Steam client.  It exists in two forms: a bridge API implemented as Winelib DLL that offers a simple C API, and a Win32 DLL that replaces the app's existing steam\_api.dll and proxies all API calls to the bridge.
