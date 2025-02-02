#pragma once
#include "EngineNameTag.h"

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
	
protected:

	virtual void Begin() = 0;
	virtual void Tick(float DeltaTime) {};

private:
	bool bIsDeath = false;
};

