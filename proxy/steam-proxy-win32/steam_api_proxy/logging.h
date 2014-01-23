// logging.h - Handles various logging (and related) utilities.

#pragma once


// FYI: Thou shall not include newlines inside of __STUB__/etc macro
//      string arguments (if possible, as it'll screw up formatting).

#define __STUB__ { __stub__(__FUNCSIG__, ""); }
#define __STUB_ARGS__(ARGS, ...) { __stub__(__FUNCSIG__, ARGS, __VA_ARGS__); }
__declspec(noreturn) void __stub__(const char *func, const char *args, ...);

#define __CANT_IMPLEMENT__ { __cant_implement__(__FUNCSIG__, ""); }
#define __CANT_IMPLEMENT_ARGS__(ARGS, ...) { __cant_implement__(__FUNCSIG__, \
    ARGS, __VA_ARGS__); }
__declspec(noreturn) void __cant_implement__(const char *func, const char *args, ...);


#define __LOG_MSG__(MSG)  __log_message__(__FUNCSIG__, MSG, "")
#define __LOG_ARGS_MSG__(MSG, ARGS, ...) __log_message__(__FUNCSIG__, MSG, \
    ARGS, __VA_ARGS__)
void __log_message__(const char *func, const char *msg, const char *args, ...);

#define __ABORT__(MSG)  __abort__(__FUNCSIG__, MSG, "")
#define __ABORT_ARGS__(MSG, ARGS, ...)  __abort__(__FUNCSIG__, MSG, ARGS, \
    __VA_ARGS__)
__declspec(noreturn) void __abort__(const char *func, const char *msg,
    const char *args, ...);

