// steam_api_bridge.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "steam_api_bridge.h"


// This is an example of an exported variable
STEAM_API_BRIDGE_API int nsteam_api_bridge=0;

// This is an example of an exported function.
STEAM_API_BRIDGE_API int fnsteam_api_bridge(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see steam_api_bridge.h for the class definition
Csteam_api_bridge::Csteam_api_bridge()
{
	return;
}
