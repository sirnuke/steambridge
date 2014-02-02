// logging.cpp - Handles various logging (and related) utilities.

#include "stdafx.h"

#include <cstdarg>
#include <cstdlib>
#include <cstdio>

#include "logging.h"
#include "types.h"

#define _STREAM stdout
#define _VA_PRINT(ARG) { \
  va_list va; \
  va_start(va, ARG); \
  vfprintf(_STREAM, ARG, va); \
  va_end(va); \
}

__declspec(noreturn) void __stub__(const char *func, const char *msg, ...)
{
  fprintf(_STREAM, "ERROR: %s ", func);
  _VA_PRINT(msg);
  fprintf(_STREAM, ": is a stub\n");
  fprintf(_STREAM,
      "\tThis means a function is unimplemented, but is likely required\n"
      "\tfor use in this app.  It may be possible to implement this function,\n"
      "\tand allow this app to continue to execute.\n");
  MessageBoxA(NULL, 
             "Stub function called!\nCheck the command line output for more information",
             APP_NAME " internal error",
             MB_ICONERROR | MB_OK);
  exit(1);
}

__declspec(noreturn) void __cant_implement__(const char *func, const char *msg, ...)
{
  fprintf(_STREAM, "ERROR: %s ", func);
  _VA_PRINT(msg);
  fprintf(_STREAM, ": cannot be implemented\n");
  fprintf(_STREAM,
      "\tThis means a function is unimplemented, but is likely required\n"
      "\tfor use in this app.  However, it is not likely possible to\n"
      "\timplement this function due to technical restrictions.\n");
  MessageBoxA(NULL, 
             "Stub function called!\nCheck the command line output for more information",
             APP_NAME " internal error",
             MB_ICONERROR | MB_OK);
  exit(1);
}

void __trace__(const char *func, const char *args, ...)
{
  fprintf(_STREAM, "TRACE: %s ", func);
  _VA_PRINT(args);
  fprintf(_STREAM, "\n");
}

void __log__(const char *func, const char *msg, ...)
{
  fprintf(_STREAM, "LOG: %s ", func);
  _VA_PRINT(msg);
  fprintf(_STREAM, "\n");
  fflush(_STREAM);
}

__declspec(noreturn) void __abort__(const char *func, const char *msg,
    const char *args, ...)
{
  fprintf(_STREAM, "ABORT: %s ", func);
  _VA_PRINT(args);
  fprintf(_STREAM, ": abort called\n");
  fprintf(_STREAM,
      "\tAn internal error of some sort has been detected, which "
      "\tlikely signifies an internal error of some sort.");
  MessageBoxA(NULL, 
             "Abort called!\nCheck the command line output for more information",
             APP_NAME " internal error",
             MB_ICONERROR | MB_OK);
  exit(1);
}

