// utils_api_code.inc - Extra code included with the generated utils_api.cpp
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

extern "C"
{

STEAM_API_PROXY_API void *SteamUtils()
{
  __TRACE("");
  return state.getSteamUtils();
}

} //extern "C"
