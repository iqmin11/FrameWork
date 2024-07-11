#pragma once
#include <thread>

// Ό³Έν :
class EngineThread
{
public:
	// constrcuter destructer
	EngineThread();
	~EngineThread();

	// delete Function
	EngineThread(const EngineThread& _Other) = delete;
	EngineThread(EngineThread&& _Other) noexcept = delete;
	EngineThread& operator=(const EngineThread& _Other) = delete;
	EngineThread& operator=(EngineThread&& _Other) noexcept = delete;

	void Start(std::string_view _ThreadName, std::function<void()> _CallBack);

	void Join()
	{
		if (CallBack != nullptr)
		{
			Thread.join();
			CallBack = nullptr;
		}
	}

	static void ThreadEnd()
	{
		End = true;
	}

	static bool IsThreadEnd()
	{
		return End;
	}

protected:

private:
	static std::atomic_bool End;
	static void ThreadBaseFunc(EngineThread* CurThread, std::string_view Name);
	
	std::thread Thread;
	std::function<void()> CallBack;
};

