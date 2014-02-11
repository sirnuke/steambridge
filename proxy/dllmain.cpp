// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "logging.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call,
  LPVOID lpReserved)
{
  __TRACE("(0x%p,%lu,0x%p])", hModule, ul_reason_for_call, lpReserved);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

