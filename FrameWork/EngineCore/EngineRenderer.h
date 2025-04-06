#pragma once
#include "EngineComponent.h"

// Ό³Έν :
class EngineRenderer : public EngineComponent
{
public:
	// constrcuter destructer
	EngineRenderer();
	~EngineRenderer();

	// delete Function
	EngineRenderer(const EngineRenderer& _Other) = delete;
	EngineRenderer(EngineRenderer&& _Other) noexcept = delete;
	EngineRenderer& operator=(const EngineRenderer& _Other) = delete;
	EngineRenderer& operator=(EngineRenderer&& _Other) noexcept = delete;

protected:
	void Begin() override;
	//void Draw();

private:

};

