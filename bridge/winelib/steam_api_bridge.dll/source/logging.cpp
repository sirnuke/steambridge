// logging.cpp - Handles various logging (and related) utilities.

#include <cstdarg>
#include <cstdlib>
#include <cstdio>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "logging.h"

#define _STREAM stderr
#define _VA_PRINT(ARG) { \
  va_list va; \
  va_start(va, ARG); \
  vfprintf(_STREAM, ARG, va); \
  va_end(va); \
}

void __abort__(const char *func, const char *msg, ...)
{
  fprintf(_STREAM, "ABORT: %s: ", func);
  _VA_PRINT(msg);
  fprintf(_STREAM,
      "\tThis means a function detected an invalid state, or other logic error.\n"
      "\tIt's likely this is due to an internal error that is handled correctly\n"
      "\tby the native steam_api library.\n");
  MessageBoxA(NULL, 
             "Function detected an invalid state!\n"
             "Check the command line output for more information.",
             APP_NAME " internal error",
             MB_ICONERROR | MB_OK);
  exit(1);
}

void __stub__(const char *func, const char *msg, ...)
{
  fprintf(_STREAM, "STUB: %s: ", func);
  _VA_PRINT(msg);
  fprintf(_STREAM,
      "\tThis means a function is unimplemented, but is likely required\n"
      "\tfor use in this app.  It may be possible to implement this function,\n"
      "\tand allow this app to continue to execute.\n");
  MessageBoxA(NULL, 
             "Stub function called!\nCheck the command line output for more information.",
             APP_NAME " internal error",
             MB_ICONERROR | MB_OK);
  exit(1);
}

void __log__(const char *func, const char *msg, ...)
{
  fprintf(_STREAM, "LOG: %s: ", func);
  _VA_PRINT(msg);
  fprintf(_STREAM, "\n");
}

