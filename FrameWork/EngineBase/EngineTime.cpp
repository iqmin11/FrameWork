#include "PrecompileHeader.h"
#include "EngineTime.h"

EngineTime EngineTime::GlobalTime;

EngineTime::EngineTime()
{
	QueryPerformanceFrequency(&Second);
	QueryPerformanceCounter(&Prev);
}

EngineTime::~EngineTime() 
{
}

void EngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

float EngineTime::TimeCheck()
{
	QueryPerformanceCounter(&Current);

	Tick = Current.QuadPart - Prev.QuadPart;

	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	Prev.QuadPart = Current.QuadPart;

	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}

