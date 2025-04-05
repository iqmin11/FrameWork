#include "PrecompileHeader.h"

#include "EngineBase/EngineTime.h"

#include "EngineCore.h"
#include "EngineLevel.h"
#include "EngineDevice.h"
#include "EngineGUI.h"

std::shared_ptr<EngineLevel> EngineCore::CurUpdatedLevel = nullptr;
std::shared_ptr<EngineLevel> EngineCore::ChangeRequestLevel = nullptr;

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
	//레벨 바꾸기
	if (HasLevelChanged())
	{
		LevelChangeProc();
	}

	//델타타임 계산
	float TimeDeltaTime = EngineTime::GlobalTime.TimeCheck();

	if (CurUpdatedLevel == nullptr)
	{
		MsgAssert("CurUpdatedLevel == nullptr");
		return;
	}

	CurUpdatedLevel->Tick(TimeDeltaTime);
	CurUpdatedLevel->ActorUpdate(TimeDeltaTime);
	CurUpdatedLevel->ActorTransformUpdate(TimeDeltaTime);
	CurUpdatedLevel->ActorLateUpdate(TimeDeltaTime);

	//EngineDevice::RenderStart();
	EngineDevice::Draw();
	//EngineDevice::RenderEnd();

	CurUpdatedLevel->ActorRelease();
}

void EngineCore::EngineBegin(std::function<void()> ContentsBegin)
{
	//EngineBegin
	EngineDevice::Initialize();
	EngineGUI::Initalize();

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
	EngineGUI::Release();
	EngineDevice::Release();
	EngineWindow::WinodwRelease();
}

bool EngineCore::HasLevelChanged()
{
	return ChangeRequestLevel != nullptr;
}

void EngineCore::LevelChangeProc()
{
	std::shared_ptr<EngineLevel> PrevLevel = std::move(CurUpdatedLevel);
	if (PrevLevel != nullptr)
	{
		PrevLevel->OnLevelExit();
	}

	ChangeRequestLevel->OnLevelEnter();
	CurUpdatedLevel = std::move(ChangeRequestLevel);
}

