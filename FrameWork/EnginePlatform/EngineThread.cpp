#include "PrecompileHeader.h"
#include "EngineThread.h"
#include "EngineBase/EngineString.h"

EngineThread::EngineThread() 
{
}

EngineThread::~EngineThread() 
{
}

void EngineThread::Start(std::string_view ThreadName, std::function<void()> CallBackFunc)
{
	CallBack = CallBackFunc;
	Thread = std::thread(ThreadBaseFunc, this, ThreadName);
}

void EngineThread::ThreadBaseFunc(EngineThread* CurThread, std::string_view Name)
{
	std::wstring WName = std::move(EngineString::AsciiToUnicode(Name.data()));
	SetThreadDescription(GetCurrentThread(), WName.c_str());
	CurThread->CallBack();
}

