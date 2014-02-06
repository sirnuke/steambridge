// logging.cpp - Handles various logging (and related) utilities.

#include <cstdlib>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <wine/debug.h>

#include "logging.h"

// NOTE: fprints(stderr) doesn't cooperate with Wine, which reimplements
//       printf* (inside MSVCRT). This causes lockups when printing
//       messages.  As a workaround, and to obtain Good Citizen Status,
//       use WINE_* (WINE_TRACE, WINE_WARN, WINE_ERR, etc).  Also,
//       unlike the Proxy's logging behavior, WINE_* functions do not
//       print out a newline.  The passed message must do this.
//       WINEDEBUG="warn+steam_bridge,trace+steam_bridge" is sufficient
//       for printing out warnings and trace mssages.

// TODO: Reallly need to print out more information in abort
// TODO: Might want a sort of pop-up warning

void __abort__()
{
  MessageBoxA(NULL, 
      "Function detected an invalid state!\n"
      "This likely is caused by an internal error, perhaps one handled "
      "correctly by the native steam_api library. Check the command line for "
      "more information.",
      "SteamBridge Abort!",
      MB_ICONERROR | MB_OK);
  exit(1);
}

void __stub__()
{
  MessageBoxA(NULL, 
      "An unimplemented function has been called. This app cannot "
      "continue to execute until this is fixed. Check the command line "
      "for more information.",
      "SteamBridge Stub!",
      MB_ICONERROR | MB_OK);
  exit(1);
}

