#pragma once
#include "EngineObject.h"

class EngineComponent : public EngineObject
{
	friend class EngineActor;
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

	inline void SetOrder(int Value)
	{
		Order = Value;
	}

	inline int GetOrder() const
	{
		return Order;
	}

protected:
	void Begin() override;

private:
	int Order = 0;
};

