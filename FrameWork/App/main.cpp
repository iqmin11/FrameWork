#include <Windows.h>
#include <EngineCore/EngineCore.h>

void TestStart()
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
	EngineCore::CoreInit(hInstance, "ChatServer", TestStart, TestEnd);
	return 0;
}