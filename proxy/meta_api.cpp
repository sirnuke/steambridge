// meta_api.cpp - Implements meta API additions to steam_api.dll

#include "stdafx.h"

#include "logging.h"
#include "steam_api_proxy.h"

#ifdef  ___STEAMBRIDGE_META_API___

#include "version.h"

// TODO: Real versions and info!
const char *steam_bridge_PROXY_INFO = "See http://github.com/sirnuke/steambridge for more information!";

extern "C"
{

STEAM_API_PROXY_API const char *Steam_proxy_version_string()
{
  return steam_bridge_VERSION_STRING;
}

STEAM_API_PROXY_API const char *Steam_proxy_info_string()
{
  return steam_bridge_PROXY_INFO;
}

} // extern "C"

#endif //___STEAMBRIDGE_META_API___

