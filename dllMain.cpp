#include <Windows.h>
#include "Windows.h"

bool WINAPI DllMain(HINSTANCE hInstace, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_DETACH) {
		Windows::Destroy();
	}
	return true;
}