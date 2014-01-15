// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STEAM_API_BRIDGE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STEAM_API_BRIDGE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef STEAM_API_BRIDGE_EXPORTS
#define STEAM_API_BRIDGE_API __declspec(dllexport)
#else
#define STEAM_API_BRIDGE_API __declspec(dllimport)
#endif

// This class is exported from the steam_api_bridge.dll
class STEAM_API_BRIDGE_API Csteam_api_bridge {
public:
	Csteam_api_bridge(void);
	// TODO: add your methods here.
};

extern STEAM_API_BRIDGE_API int nsteam_api_bridge;

STEAM_API_BRIDGE_API int fnsteam_api_bridge(void);
