// meta_api.cpp - Implements meta API additions to steam_api.dll

#include "stdafx.h"

#include "logging.h"
#include "steam_api_proxy.h"


#ifdef  ___STEAMBRIDGE_META_API___

// TODO: Real versions and info!
const char *steambridge_version = "0";
const char *steambridge_info = "TODO: Real information here of some sort!";

extern "C"
{

STEAM_API_PROXY_API const char *Steam_proxy_version_string()
{
  return steambridge_version;
}

STEAM_API_PROXY_API const char *Steam_proxy_info_string()
{
  return steambridge_info;
}

} // extern "C"

#endif //___STEAMBRIDGE_META_API___

