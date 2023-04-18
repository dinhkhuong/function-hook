#include "Memory.h"

typedef char*(__cdecl * _ACPrintF)(char * sFormat, ...);
_ACPrintF ACPrintF;

DWORD WINAPI MainThread(LPVOID param)
{
	uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
	ACPrintF = (_ACPrintF)(base + 0x1780);

	char* sFormat = "%s:\f%d %s";

	ACPrintF(sFormat, "hook", 1, "Loaded...");

	while (!GetAsyncKeyState(VK_END))
	{
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			ACPrintF(sFormat, "Str1", 1, "str2");
		}
	}

	ACPrintF(sFormat, "hook", 1, "Unloading...");
	FreeLibraryAndExitThread((HMODULE)param, 0);
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, MainThread, hModule, 0, 0);
		break;
	default:
		break;
	}
	return TRUE;
}