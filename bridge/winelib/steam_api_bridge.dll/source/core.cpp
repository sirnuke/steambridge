// core.cpp - Handles the core API calls

#include <cstdio>

#include <steam_api.h>

#include "api.h"


extern "C"
{

bool steam_bridge_SteamAPI_InitSafe()
{
  return SteamAPI_InitSafe();
}

}
