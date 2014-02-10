// steam_api_bridge.h - Mostly just includes the bridge API
#pragma once

#ifdef STEAM_API_BRIDGE_EXPORTS
#define STEAM_API_BRIDGE_API __declspec(dllexport)
#else
#define STEAM_API_BRIDGE_API __declspec(dllimport)
#endif

#include <api.h>
