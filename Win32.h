#pragma once

#include <Windows.h>

#ifdef WINDOWS_EXPORTS
#define WIN_API __declspec(dllexport)
#else
#define WIN_API __declspec(dllimport)
#pragma comment(lib,"Windows.lib")
#endif

extern "C"{
	WIN_API void WindowCreate(HINSTANCE hInstance, LPWSTR Title, int *nCmdShow, 
		int x = 1280, int y = 720);
	WIN_API void MainLoop(void (*)());
	WIN_API void Run();
}

extern "C"{
	WIN_API HWND GetHWND();
}