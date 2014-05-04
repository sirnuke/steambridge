// friends_api_code.inc - Extra code included with the generated friends_api.cpp
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

extern "C"
{

STEAM_API_PROXY_API void *SteamUserStats()
{
  __TRACE("()");
  return state.getSteamUserStats();
}

} // extern "C"
