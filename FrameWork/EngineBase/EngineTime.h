#pragma once

// Ό³Έν :
class EngineTime
{
public:
	static EngineTime GlobalTime;

	// constrcuter destructer
	EngineTime();
	~EngineTime();

	// delete Function
	EngineTime(const EngineTime& _Other) = delete;
	EngineTime(EngineTime&& _Other) noexcept = delete;
	EngineTime& operator=(const EngineTime& _Other) = delete;
	EngineTime& operator=(EngineTime&& _Other) noexcept = delete;

	void Reset();

	float TimeCheck();

protected:

private:
	__int64 Tick = 0;
	LARGE_INTEGER Prev = LARGE_INTEGER();
	LARGE_INTEGER Current = LARGE_INTEGER();
	LARGE_INTEGER Second = LARGE_INTEGER();
	double DoubleDeltaTime = 0.0;
	float floatDeltaTime = 0.0;
};

