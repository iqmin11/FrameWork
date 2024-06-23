#pragma once
#include "EngineCore/EngineGUI.h"

// Ό³Έν :
class TestGUI : public EngineGUIWindow
{
public:
	// constrcuter destructer
	TestGUI();
	~TestGUI();

	// delete Function
	TestGUI(const TestGUI& _Other) = delete;
	TestGUI(TestGUI&& _Other) noexcept = delete;
	TestGUI& operator=(const TestGUI& _Other) = delete;
	TestGUI& operator=(TestGUI&& _Other) noexcept = delete;

protected:

private:
	void Begin() override;
	void Tick(float DeltaTime) override;
};

