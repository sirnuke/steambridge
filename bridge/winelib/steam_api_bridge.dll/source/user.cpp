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

STEAM_API_BRIDGE_API void *steam_bridge_SteamUser_GetSteamID(class ISteamUser *steamUser)
{
  WINE_TRACE("(%p)\n", steamUser);

  if (!steamUser)
    __ABORT("NULL steamUser pointer!");
  // Confirm the size is 8bytes, which is required per the headers
  // TODO: There's better places to store this
  if (sizeof(CSteamID) != 8)
    __ABORT("CSteamID doesn't match the expected size! "
        " (Should be 64bits/8bytes) (%zu/8)", sizeof(CSteamID));

  uint64 id = steamUser->GetSteamID().ConvertToUint64();
  context->setSteamID(id);
  // TODO: returning 64-bit values (such as here) in 32-bit mode means
  //       EAX is set to a the location of a hidden struct containing the
  //       value.  Despite adding -ret64, Winelib doesn't seem to be
  //       handling this correctly, and just dumps the entire value
  //       in EAX.  This 'fits' fine, but the win32 Proxy tries to read
  //       this value as a pointer, and blows up accordingly.  As an
  //       immediate work around, store this value in the context and
  //       return that memory location.
  WINE_TRACE("Get steamUser ID of %lu->%p\n", id, context->getSteamIDPointer());
  return context->getSteamIDPointer();
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUser_BLoggedOn(class ISteamUser *steamUser)
{
  WINE_TRACE("(0x%p)\n", steamUser);

  if (!steamUser)
    __ABORT("NULL steamUser pointer!");

  return steamUser->BLoggedOn();
}

STEAM_API_BRIDGE_API class ISteamUser *steam_bridge_SteamUser()
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

