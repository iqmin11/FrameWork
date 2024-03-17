#pragma once

//std
#include <functional>

//myClass
#include <EnginePlatform/EngineWindow.h>

class EngineCore
{
public:
	// construtor destructor
	EngineCore();
	~EngineCore();

	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	static void CoreInit(HINSTANCE hInst,
		std::string_view TitleName, 
		std::function<void()> Begin, 
		std::function<void()> End, 
		const float4& WindowPos = EngineWindow::DefaultWindowPos,
		const float4& WindowSize = EngineWindow::DefaultWindowSize);

	static void CoreTick();


protected:


private:
	static void EngineBegin(std::function<void()> ContentsBegin = nullptr);
	static void EngineEnd(std::function<void()> ContentsEnd = nullptr);
};

