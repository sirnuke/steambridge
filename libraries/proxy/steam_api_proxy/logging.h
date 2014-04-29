// logging.h - Handles various logging (and related) utilities.
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#pragma once


// FYI: Thou shall not include newlines inside of __STUB__/etc macro
//      string arguments (if possible, as it'll screw up formatting).

#define __STUB(ARGS, ...) { __stub__(__FUNCSIG__, ARGS, __VA_ARGS__); }
__declspec(noreturn) void __stub__(const char *func, const char *args, ...);

#define __CANT_IMPLEMENT(ARGS, ...) { __cant_implement__(__FUNCSIG__, ARGS, \
    __VA_ARGS__); }
__declspec(noreturn) void __cant_implement__(const char *func,
    const char *args, ...);

// TODO: Compile time option to turn TRACE on/off
#define __TRACE(ARGS, ...) __trace__(__FUNCSIG__, ARGS, __VA_ARGS__)
void __trace__(const char *func, const char *args, ...);

#define __LOG(MSG, ...) __log__(__FUNCSIG__, MSG, __VA_ARGS__)
void __log__(const char *func, const char *msg, ...);

#define __ABORT(MSG, ...)  __abort__(__FUNCSIG__, MSG, __VA_ARGS__)
__declspec(noreturn) void __abort__(const char *func, const char *msg, ...);

