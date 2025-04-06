#pragma once
#include "EngineNameTag.h"
#include "EngineTransform.h"

class EngineObject : public std::enable_shared_from_this<EngineObject>, public EngineNameTag
{
public:
	// construtor destructor
	EngineObject();
	virtual ~EngineObject();

	// delete Function
	EngineObject(const EngineObject& _Other) = delete;
	EngineObject(EngineObject&& _Other) noexcept = delete;
	EngineObject& operator=(const EngineObject& _Other) = delete;
	EngineObject& operator=(EngineObject&& _Other) noexcept = delete;

	bool IsDeath() const
	{
		return bIsDeath;
	}

	EngineTransform& GetTransformRef()
	{
		return Transform;
	}

protected:

	void Init_Internal() // Use In Only Engine, Not Virtual Function
	{
		//������ shared_from_this�� �����ڿ��� ȣ���� �Ұ��� �߱� ������ ����� ���.
		Transform.SetMaster(shared_from_this());
	};

	// For User
	virtual void Begin() = 0;
	virtual void Tick(float DeltaTime) {};

private:
	bool bIsDeath = false;
	bool bIsUpdate = false;

	EngineTransform Transform;
};

