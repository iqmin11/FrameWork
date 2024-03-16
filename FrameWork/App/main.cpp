#include <Windows.h>
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>

void TestStart()
{
	int a = 0;
}

void TestTick()
{
	int a = 0;
}

void TestEnd()
{
	int a = 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	EngineDebug::LeakCheck();
	EngineWindow::WindowCreate(hInstance, "Test");
	EngineWindow::WindowLoop(TestStart, TestTick, TestEnd);

	return 0;
}