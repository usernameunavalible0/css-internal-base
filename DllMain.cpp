#include "Entry/Entry.h"

DWORD APIENTRY MainThread(LPVOID lpParam)
{
	G::Entry.Load();

	while (!GetAsyncKeyState(VK_F11))
		Sleep(420);

	G::Entry.Unload();

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	static bool s_bAttached = false;

	if ((fdwReason == DLL_PROCESS_ATTACH) && !s_bAttached)
	{
		const HANDLE hMain = CreateThread(NULL, NULL, MainThread, hinstDLL, NULL, NULL);

		if (hMain)
		{
			s_bAttached = true;
			CloseHandle(hMain);
		}
	}

	return TRUE;
}