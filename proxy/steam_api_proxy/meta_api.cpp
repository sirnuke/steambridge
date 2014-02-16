// meta_api.cpp - Implements meta API additions to steam_api.dll

#include "stdafx.h"

#include "logging.h"
#include "steam_api_proxy.h"

#ifdef  ___STEAMBRIDGE_META_API___

#include "config.h"

// TODO: Real versions and info!
const char *steam_bridge_INFO = "Visit " _STEAM_BRIDGE_WEBPAGE 
  " for more information on " _STEAM_BRIDGE_APPNAME "!";

extern "C"
{

STEAM_API_PROXY_API const char *Steam_proxy_version_string()
{
  return _STEAM_BRIDGE_VERSION_LONG;
}

STEAM_API_PROXY_API const char *Steam_proxy_info_string()
{
  return steam_bridge_INFO;
}

} // extern "C"

#endif //___STEAMBRIDGE_META_API___

