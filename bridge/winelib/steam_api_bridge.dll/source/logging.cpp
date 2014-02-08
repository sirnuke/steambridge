// logging.cpp - Handles various logging (and related) utilities.

#include <cstdarg>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <string>
#include <sstream>

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
//       WINEDEBUG="+steam_bridge" is helpful for debug info.

// TODO: Reallly need to print out more information in abort
// TODO: Might want a sort of pop-up warning

void __abort__(const char *func, const char *msg, ...)
{
  std::stringstream ss;
  ss << "Invalid state detected!\n\n";
  ss << "Abort called in (" << func << "): ";
  {
    char temp[513]; // pffffft
    memset(temp, 0, 513); // pffffffft
    va_list va;
    va_start(va, msg);
    vsnprintf(temp, 512, msg, va); // pfffft
    va_end(va);
    ss << temp;
  }
  ss << "\n\n";
  ss << "This is liksley caused by an internal error, perhaps indicating ";
  ss << "a situation handled correctly by the real steam_api library. More ";
  ss << "information may be available on the command line.";
  std::string s = ss.str();
  MessageBoxA(NULL, 
      s.c_str(),
      "SteamBridge Abort!",
      MB_ICONERROR | MB_OK);
  exit(1);
}

