#pragma once
#include "EngineNameTag.h"
#include "EngineTransform.h"

class EngineLevel;
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

	std::shared_ptr<EngineLevel> GetOwnerLevel()
	{
		return OwnerLevel.lock();
	}

	template <typename CastingType>
	std::shared_ptr<CastingType> SharedCastingThis()
	{
		return std::static_pointer_cast<CastingType>(shared_from_this());
	}

protected:

	void Init_Internal(std::shared_ptr<EngineLevel> CurLevel) // Use In Only Engine, Not Virtual Function
	{
		//������ shared_from_this�� �����ڿ��� ȣ���� �Ұ��� �߱� ������ ����� ���.
		Transform.SetMaster(shared_from_this());
		SetOwnerLevel(CurLevel);
	};

	// For User
	virtual void Begin() = 0;
	virtual void Tick(float DeltaTime) {};

private:
	bool bIsDeath = false;
	bool bIsUpdate = false;

	EngineTransform Transform;

	std::weak_ptr<EngineLevel> OwnerLevel;

	void SetOwnerLevel(std::shared_ptr<EngineLevel> CurLevel)
	{
		if (!OwnerLevel.expired())
		{
			MsgAssert("OwnerLevel�� �ٲ� �� �����ϴ�");
		}

		OwnerLevel = CurLevel;
	}
};

