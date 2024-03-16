#pragma once
#include <assert.h>
#include <crtdbg.h>
#include <string>
#include <Windows.h>

namespace EngineDebug
{
	inline static void LeakCheck()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}
};

#define MsgAssert(MsgText) MessageBoxA(nullptr,	MsgText, "Error", MB_OK); assert(false);
