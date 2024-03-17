#pragma once
#include "EngineObject.h"

class EngineActor : public EngineObject
{
public:
	// construtor destructor
	EngineActor();
	~EngineActor();

	// delete Function
	EngineActor(const EngineActor& _Other) = delete;
	EngineActor(EngineActor&& _Other) noexcept = delete;
	EngineActor& operator=(const EngineActor& _Other) = delete;
	EngineActor& operator=(EngineActor&& _Other) noexcept = delete;

protected:
	void Begin() override;
	void Tick(float DeltaTime) override;

private:

};

