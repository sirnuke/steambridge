// steam_api_proxy.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <sstream>
#include <string>

#include "steam_api_proxy.h"

__declspec(noreturn) static void __stub(const char *function)
{
  printf("Function %s is not implemented!\n", function);
  // TODO: Make this into a popup message box?
  exit(0);
}

extern "C"
{

STEAM_API_PROXY_API HSteamPipe GetHSteamPipe()
{
  return SteamAPI_GetHSteamPipe();
}

STEAM_API_PROXY_API HSteamUser GetHSteamUser()
{
  return SteamAPI_GetHSteamUser();
}

STEAM_API_PROXY_API HSteamPipe SteamAPI_GetHSteamPipe()
{
  __stub(__FUNCSIG__);
}

STEAM_API_PROXY_API HSteamUser SteamAPI_GetHSteamUser()
{
  __stub(__FUNCSIG__);
}

STEAM_API_PROXY_API const char *SteamAPI_GetSteamInstallPath()
{
  __stub(__FUNCSIG__);
}

} // extern "C"

