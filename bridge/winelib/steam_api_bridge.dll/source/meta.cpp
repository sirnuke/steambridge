// meta.cpp - Implements various meta API calls.

#include <cstdio>

#include <string>

#define NOMINMAX
#include <windef.h>
#include <winbase.h>
#include <wine/debug.h>

#include <steam_api.h>

#include "api.h"
#include "logging.h"

const std::string _bridge_version = "0";
const std::string _bridge_info = "TODO: Put something interesting here";

STEAM_API_BRIDGE_API const char *steam_bridge_version_string()
{
  return _bridge_version.c_str();
}

STEAM_API_BRIDGE_API const char *steam_bridge_info_string()
{
  return _bridge_info.c_str();
}

