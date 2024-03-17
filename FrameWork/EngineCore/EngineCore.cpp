#include "EngineCore.h"

EngineCore::EngineCore()
{

}

EngineCore::~EngineCore()
{

}

void EngineCore::CoreInit(HINSTANCE hInst, std::string_view TitleName, std::function<void()> Start, std::function<void()> End, const float4& WindowPos, const float4& WindowSize)
{
	EngineDebug::LeakCheck();
	EngineWindow::WindowCreate(hInst, TitleName, WindowPos, WindowSize);
	EngineWindow::WindowLoop(std::bind(EngineBegin, Start), CoreTick, std::bind(EngineEnd, End));
}

void EngineCore::CoreTick()
{
	int a = 0;
}

void EngineCore::EngineBegin(std::function<void()> ContentsBegin)
{
	//EngineBegin

	//ContentsBegin
	if (ContentsBegin != nullptr)
	{
		ContentsBegin();
	}
}

void EngineCore::EngineEnd(std::function<void()> ContentsEnd)
{
	//ContentsEnd
	if (ContentsEnd != nullptr)
	{
		ContentsEnd();
	}
	
	//EngineEnd
	EngineWindow::WinodwRelease();
}

