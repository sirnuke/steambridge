// logging.h - Handles various logging (and related) utilities.

#ifndef  ___STEAM_API_BRIDGE_LOGGING_H___
#define  ___STEAM_API_BRIDGE_LOGGING_H___

#define APP_NAME "SteamAPIBridge"

// FYI: Thou shall not include newlines inside of __STUB/etc macro
//      string arguments (if possible, as it'll screw up formatting).

#define __ABORT(MSG, ...) __abort__(__PRETTY_FUNCTION__, MSG, ##__VA_ARGS__)
void __abort__(const char *func, const char *msg, ...)
  __attribute__ ((noreturn));

#define __STUB(ARGS, ...) { __stub__(__PRETTY_FUNCTION__ , ARGS, ##__VA_ARGS__); }
void __stub__(const char *func, const char *args, ...)
  __attribute__ ((noreturn));

#define __LOG(MSG, ...) __log__(__PRETTY_FUNCTION__ , MSG, ##__VA_ARGS__)
void __log__(const char *func, const char *msg, ...);

#endif //___STEAM_API_BRIDGE_LOGGING_H___

