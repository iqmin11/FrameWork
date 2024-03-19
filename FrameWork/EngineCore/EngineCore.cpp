#include "PrecompileHeader.h"

#include "EngineCore.h"
#include "EngineLevel.h"
#include "EngineDevice.h"

std::shared_ptr<EngineLevel> EngineCore::CurUpdatedLevel = nullptr;
std::map<std::string, std::shared_ptr<EngineLevel>> EngineCore::LevelManager;

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
	float TempTime = 0.f;

	if (CurUpdatedLevel == nullptr)
	{
		MsgAssert("CurUpdatedLevel == nullptr");
		return;
	}

	CurUpdatedLevel->Tick(TempTime);
	int a = 0;
}

void EngineCore::EngineBegin(std::function<void()> ContentsBegin)
{
	//EngineBegin
	EngineDevice::Initialize();

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
	EngineDevice::Release();
	EngineWindow::WinodwRelease();
}

