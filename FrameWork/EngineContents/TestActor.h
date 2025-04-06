#pragma once
#include <EngineCore\EngineActor.h>

// Ό³Έν :
class TestActor : public EngineActor
{
public:
	// constrcuter destructer
	TestActor();
	~TestActor();

	// delete Function
	TestActor(const TestActor& _Other) = delete;
	TestActor(TestActor&& _Other) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(TestActor&& _Other) noexcept = delete;

protected:
	void Begin();
	void Tick(float DeltaTime) override;

private:
	std::weak_ptr<class EngineRenderer> RendererComp;
};

