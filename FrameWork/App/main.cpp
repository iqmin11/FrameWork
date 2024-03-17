#include <Windows.h>
#include <EngineCore/EngineCore.h>
#include <EngineContents/ContentsCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	EngineCore::CoreInit(hInstance, "ChatServer", ContentsCore::ContentsBegin, ContentsCore::ContentsEnd);
	return 0;
}