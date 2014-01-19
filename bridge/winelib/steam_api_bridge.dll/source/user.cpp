// user.cpp - Implements various functions related to the ISteamUser class.

#include <cstdio>

#include <steam_api.h>

#include <windef.h>
#include <winbase.h>
#include <wine/debug.h>

#include "api.h"
#include "core.h"
#include "logging.h"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);


extern "C"
{

STEAM_API_BRIDGE_API uint64 steam_bridge_SteamUser_GetSteamID(class ISteamUser *steamUser)
{
  WINE_TRACE("(0x%p)", steamUser);

  if (!steamUser)
    __ABORT_ARGS__("NULL steamUser pointer!", "(0x%p)", steamUser);
  // Confirm the size is 8bytes, which is required per the headers
  if (sizeof(CSteamID) != 8)
    __ABORT_ARGS__("CSteamID doesn't match the expected size! "
        "(Should be 64bits/8bytes)", "(%lu/8)", sizeof(CSteamID));

  return steamUser->GetSteamID().ConvertToUint64();
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUser_BLoggedOn(class ISteamUser *steamUser)
{
  WINE_TRACE("(0x%p)", steamUser);

  if (!steamUser)
    __ABORT_ARGS__("NULL steamUser pointer!", "(0x%p)", steamUser);

  return steamUser->BLoggedOn();
}

STEAM_API_BRIDGE_API class ISteamUser *steam_bridge_SteamUser()
{
  WINE_TRACE("()");

  if (!context)
  {
    WINE_WARN("Context is NULL, Init either failed or wasn't called");
    return NULL;
  }

  return context->getSteamUser();
}

} // extern "C"

