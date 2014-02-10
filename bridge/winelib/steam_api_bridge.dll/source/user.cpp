// user.cpp - Implements various functions related to the ISteamUser class.

#include <cstdio>

#include <steam_api.h>

#define NOMINMAX
#include <windef.h>
#include <winbase.h>
#include <wine/debug.h>

#include "api.h"
#include "core.h"
#include "logging.h"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

extern "C"
{

STEAM_API_BRIDGE_API CSteamID steam_bridge_SteamUser_GetSteamID(ISteamUser *steamUser)
{
  WINE_TRACE("(%p)\n", steamUser);

  if (!steamUser)
    __ABORT("NULL steamUser pointer!");
  // Confirm the size is 8bytes, which is required per the headers
  // TODO: There's better places to store this
  if (sizeof(CSteamID) != 8)
    __ABORT("CSteamID doesn't match the expected size! "
        " (Should be 64bits/8bytes) (%zu/8)", sizeof(CSteamID));

  CSteamID id = steamUser->GetSteamID();
  WINE_TRACE("Got steamUser ID of %llu\n", id.ConvertToUint64());
  return id;
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUser_BLoggedOn(ISteamUser *steamUser)
{
  WINE_TRACE("(0x%p)\n", steamUser);

  if (!steamUser)
    __ABORT("NULL steamUser pointer!");

  return steamUser->BLoggedOn();
}

STEAM_API_BRIDGE_API int steam_bridge_SteamUser_InitiateGameConnection(
    ISteamUser *steamUser, void *pAuthBlob, int cbMaxAuthBlob,
    CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer,
    bool bSecure)
{
  WINE_TRACE("(0x%p,0x%p,%i,%llu,%u,%hu,%i)\n", steamUser, pAuthBlob,
      cbMaxAuthBlob, steamIDGameServer.ConvertToUint64(), unIPServer,
      usPortServer, bSecure);

  return steamUser->InitiateGameConnection(pAuthBlob, cbMaxAuthBlob,
      steamIDGameServer, unIPServer, usPortServer, bSecure);
}

STEAM_API_BRIDGE_API void steam_bridge_SteamUser_TerminateGameConnection(
    ISteamUser *steamUser, uint32 unIPServer, uint16 usPortServer)
{
  WINE_TRACE("(0x%p,%u,%hu)\n", steamUser, unIPServer, usPortServer);

  return steamUser->TerminateGameConnection(unIPServer, usPortServer);
}

STEAM_API_BRIDGE_API ISteamUser *steam_bridge_SteamUser()
{
  WINE_TRACE("\n");

  if (!context)
  {
    WINE_ERR("Context is NULL, Init either failed or wasn't called\n");
    return NULL;
  }

  return context->getSteamUser();
}

} // extern "C"

