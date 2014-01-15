// steam_api_bridge.cpp - Stub's the public bridge API
//

#include "stdafx.h"

#include <cstdlib>

#include "steam_api_bridge.h"

#define __STUB__ { __stub__(); }
 __declspec(noreturn) void __stub__()
 {
   exit(1);
 }

extern "C"
{
  STEAM_API_BRIDGE_API int steam_bridge_say_hello() __STUB__
}
