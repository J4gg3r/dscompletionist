#include <windows.h>
#include "game.h"
#include "d3d9.h"
#include "logger.h"

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
			begin_log("E:\\DSRadar.txt");
			Hooks::Initialize();
			break;

		case DLL_PROCESS_DETACH:
			Hooks::Release();
			end_log();
			break;

		default:
			break;
	}

	return TRUE;
}
