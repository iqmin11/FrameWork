#pragma once
#include "EngineObject.h"
#include "EngineLevel.h"
#include "EngineComponent.h"

class EngineActor : public EngineObject
{
	friend class EngineLevel;
public:
	// construtor destructor
	EngineActor();
	~EngineActor();

	// delete Function
	EngineActor(const EngineActor& _Other) = delete;
	EngineActor(EngineActor&& _Other) noexcept = delete;
	EngineActor& operator=(const EngineActor& _Other) = delete;
	EngineActor& operator=(EngineActor&& _Other) noexcept = delete;

	template <typename ComponentType> 
	std::shared_ptr<ComponentType> CreateComponent()
	{
		std::shared_ptr<EngineComponent> NewComponent = std::make_shared<ComponentType>();

		NewComponent->Init_Internal();
		EngineTransform& ChildTransform = NewComponent->GetTransformRef();
		EngineTransform& ParentTransform = this->GetTransformRef();
		ChildTransform->SetParent(ParentTransform); //컴포넌트 관리는 트랜스폼에서
		NewComponent->Begin();

		return std::dynamic_pointer_cast<ComponentType>(NewComponent);
	}

protected:
	void Begin() override;
	void Tick(float DeltaTime) override;

private:
	
};

