// logging.h - Handles various logging (and related) utilities.

#ifndef  ___STEAM_API_BRIDGE_LOGGING_H___
#define  ___STEAM_API_BRIDGE_LOGGING_H___

#define APP_NAME "SteamAPIBridge"

// FYI: Thou shall not include newlines inside of __STUB__/etc macro
//      string arguments (if possible, as it'll screw up formatting).

#define __ABORT__(MSG) __abort__(__PRETTY_FUNCTION__, MSG, "")
#define __ABORT_ARGS__(MSG, ARGS, ...) __abort__(__PRETTY_FUNCTION__, MSG, ARGS, __VA_ARGS__)
void __abort__(const char *func, const char *msg, const char *args, ...) 
  __attribute__ ((noreturn));

#define __STUB__ { __stub__(__PRETTY_FUNCTION__ , ""); }
#define __STUB_ARGS__(ARGS, ...) { __stub__(__PRETTY_FUNCTION__ , ARGS, __VA_ARGS__); }
void __stub__(const char *func, const char *args, ...) __attribute__ ((noreturn));

#define __LOG_MSG__(MSG)  __log_message__(__PRETTY_FUNCTION__ , MSG, "")
#define __LOG_ARGS_MSG__(MSG, ARGS, ...) __log_message__(__PRETTY_FUNCTION__ , MSG, ARGS, __VA_ARGS__)
void __log_message__(const char *func, const char *msg, const char *args, ...);

#endif //___STEAM_API_BRIDGE_LOGGING_H___

