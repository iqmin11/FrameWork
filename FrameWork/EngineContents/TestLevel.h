#pragma once
#include <EngineCore/EngineLevel.h>

class TestLevel : public EngineLevel
{
public:
	// construtor destructor
	TestLevel();
	~TestLevel();

	// delete Function
	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

protected:
	void Begin() override;
	void Tick(float DeltaTime) override;

private:

};

