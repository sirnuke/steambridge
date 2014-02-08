// steam_api_bridge.h - Mostly just includes the bridge API
#pragma once

#ifdef STEAM_API_BRIDGE_EXPORTS
#define STEAM_API_BRIDGE_API __declspec(dllexport)
#else
#define STEAM_API_BRIDGE_API __declspec(dllimport)
#endif

typedef unsigned char uint8;
typedef signed char int8;

typedef __int16 int16;
typedef unsigned __int16 uint16;
typedef __int32 int32;
typedef unsigned __int32 uint32;
typedef __int64 int64;
typedef unsigned __int64 uint64;

typedef __int32 intp;
typedef unsigned __int32 uintp;

typedef uint32 AppId_t;

typedef uint64 SteamAPICall_t;


#include <api.h>
