// logging.cpp - Handles various logging (and related) utilities.

#include "stdafx.h"

#include <cstdarg>
#include <cstdlib>
#include <cstdio>

#include "logging.h"
#include "types.h"

__declspec(noreturn) void __stub__(const char *func, const char *msg, ...)
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
             "Stub function called!\nCheck the command line output for more information",
             APP_NAME " internal error",
             MB_ICONERROR | MB_OK);
  va_end(va);
  exit(1);
}

__declspec(noreturn) void __cant_implement__(const char *func, const char *msg, ...)
{
  printf("%s ", func);
  va_list va;
  va_start(va, msg);
  vprintf(msg, va);
  printf(": cannot be implemented\n");
  printf("\tThis means a function is unimplemented, but is likely required\n"
         "\tfor use in this app.  However, it is not likely possible to\n"
         "\timplement this function due to technical restrictions.\n");
  MessageBoxA(NULL, 
             "Stub function called!\nCheck the command line output for more information",
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

__declspec(noreturn) void __abort__(const char *func, const char *msg,
    const char *args, ...)
{
  printf("%s ", func);
  va_list va;
  va_start(va, msg);
  vprintf(msg, va);
  printf(": abort called\n");
  printf("\tAn internal error of some sort has been detected, which "
         "\tlikely signifies an internal error of some sort.");
  MessageBoxA(NULL, 
             "Abort called!\nCheck the command line output for more information",
             APP_NAME " internal error",
             MB_ICONERROR | MB_OK);
  va_end(va);
  exit(1);
}

