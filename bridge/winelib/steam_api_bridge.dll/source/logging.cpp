// logging.cpp - Handles various logging (and related) utilities.

#include <cstdarg>
#include <cstdlib>
#include <cstdio>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "logging.h"

void __abort__(const char *func, const char *msg, const char *args, ...)
{
  printf("%s ", func);
  va_list va;
  va_start(va, args);
  vprintf(args, va);
  printf(": %s\n", msg);
  printf("\tThis means a function detected an invalid state, or other logic error.\n"
         "\tIt's likely this is due to an internal error that is handled correctly\n"
         "\tby the native steam_api library.\n");
  MessageBoxA(NULL, 
             "Function detected an invalid state!\n"
             "Check the command line output for more information.",
             APP_NAME " internal error",
             MB_ICONERROR | MB_OK);
  va_end(va);
  exit(1);
}

void __stub__(const char *func, const char *msg, ...)
{
  printf("%s ", func);
  va_list va;
  va_start(va, msg);
  vprintf(msg, va);
  printf(": is a stub\n");
  printf("\tThis means a function is unimplemented, but is likely required\n"
         "\tfor use in this app.  It may be possible to implement this function,\n"
         "\tand allow this app to continue to execute.\n");
  MessageBoxA(NULL, 
             "Stub function called!\nCheck the command line output for more information.",
             APP_NAME " internal error",
             MB_ICONERROR | MB_OK);
  va_end(va);
  exit(1);
}

void __log_message__(const char *func, const char *msg, const char *args, ...)
{
  printf("%s ", func);
  va_list va;
  va_start(va, args);
  vprintf(args, va);
  printf(": %s\n", msg);
}

