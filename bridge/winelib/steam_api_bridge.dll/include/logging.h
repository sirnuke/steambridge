// logging.h - Handles various logging (and related) utilities.

#ifndef  ___STEAM_API_BRIDGE_LOGGING_H___
#define  ___STEAM_API_BRIDGE_LOGGING_H___

#define __ABORT(MSG, ...) __abort__(__PRETTY_FUNCTION__, MSG, ##__VA_ARGS__)

void __abort__(const char *func, const char *msg, ...) 
  __attribute__ ((noreturn));

#endif //___STEAM_API_BRIDGE_LOGGING_H___

