#pragma once
#include "EngineObject.h"

class EngineComponent : public EngineObject
{
public:
	// construtor destructor
	EngineComponent();
	~EngineComponent();

	// delete Function
	EngineComponent(const EngineComponent& _Other) = delete;
	EngineComponent(EngineComponent&& _Other) noexcept = delete;
	EngineComponent& operator=(const EngineComponent& _Other) = delete;
	EngineComponent& operator=(EngineComponent&& _Other) noexcept = delete;

	const std::shared_ptr<EngineObject> GetParent();

protected:
	void Begin() override;

private:

};

