#pragma once
#include <assert.h>
#include <crtdbg.h>
#include <string>
#include <Windows.h>

class EngineDebug
{
public:
	// construtor destructor
	EngineDebug();
	~EngineDebug();

	// delete Function
	EngineDebug(const EngineDebug& _Other) = delete;
	EngineDebug(EngineDebug&& _Other) noexcept = delete;
	EngineDebug& operator=(const EngineDebug& _Other) = delete;
	EngineDebug& operator=(EngineDebug&& _Other) noexcept = delete;

	inline static void LeakCheck()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

protected:


private:

};

#define MsgAssert(MsgText) MessageBoxA(nullptr,	MsgText, "Error", MB_OK); assert(false);
