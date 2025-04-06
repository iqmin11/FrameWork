#pragma once
#include "EngineObject.h"
#include "EngineLevel.h"

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

	template <typename ComponentType, typename EnumType>
	std::shared_ptr<ComponentType> CreateComponent(EnumType Order)
	{
		return CreateComponent(static_cast<EnumType>(Order));
	}

	template <typename ComponentType> 
	std::shared_ptr<ComponentType> CreateComponent(int Order = 0)
	{
		std::shared_ptr<class EngineComponent> NewComponent = std::make_shared<ComponentType>();
		NewComponent->Init_Internal(GetOwnerLevel());
		EngineTransform& ChildTransform = NewComponent->GetTransformRef();
		EngineTransform& ParentTransform = this->GetTransformRef();
		ChildTransform.SetParent(&ParentTransform); //������Ʈ ������ Ʈ����������
		
		NewComponent->SetOrder(Order); //���⼭�� ����� �ִ� ������ �����һ�, ���� ������ ����Ϸ���, �����̳ʿ� ���� ������ �Ҽ� �ֵ��� ��������
		
		NewComponent->Begin();

		return std::static_pointer_cast<ComponentType>(NewComponent);
	}


protected:
	void Begin() override;
	void Tick(float DeltaTime) override;

private:
};


