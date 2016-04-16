#include "Win32.h"
#include "Windows.h"

void WindowCreate(HINSTANCE hInstance, LPWSTR Title, int *nCmdShow, int x, int y){
	return Windows::GetSingleton()->Create(hInstance, Title, nCmdShow, x, y);
}
void MainLoop(void (*render)()){
	Windows::GetSingleton()->Render = render;
}

void Run(){
	return Windows::GetSingleton()->Run();
}

HWND GetHWND(){return Windows::GetSingleton()->Gethwnd();}