// logging.h - Handles various logging (and related) utilities.

#pragma once


// FYI: Thou shall not include newlines inside of __STUB__/etc macro
//      string arguments (if possible, as it'll screw up formatting).

#define __STUB__ { __stub__(__FUNCSIG__, ""); }
#define __STUB_MSG__(MSG, ...) { __stub__(__FUNCSIG__, MSG, __VA_ARGS__); }
__declspec(noreturn) void __stub__(const char *func, const char *msg, ...);

#define __CANT_IMPLEMENT__ { __cant_implement__(__FUNCSIG__, ""); }
#define __CANT_IMPLEMENT_MSG__(MSG, ...) { __cant_implement__(__FUNCSIG__, MSG, __VA_ARGS__); }
__declspec(noreturn) void __cant_implement__(const char *func, const char *msg, ...);


#define __LOG_MSG__(MSG, ...) __log_message__(__FUNCSIG__, MSG, __VA_ARGS__)
void __log_message__(const char *func, const char *msg, ...);

