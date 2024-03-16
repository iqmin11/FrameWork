#include <Windows.h>
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	EngineDebug::LeakCheck();
	
	//½Å·ÚÀÇ ¸¯
	int* a = new int;

	EngineWindow::WindowCreate(hInstance, "Test");
	EngineWindow::WindowLoop();

	return 1;
}