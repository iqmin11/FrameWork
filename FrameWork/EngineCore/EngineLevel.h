#pragma once
#include "EngineActor.h"

class EngineLevel : public EngineActor
{
public:
	// construtor destructor
	EngineLevel();
	~EngineLevel();

	// delete Function
	EngineLevel(const EngineLevel& _Other) = delete;
	EngineLevel(EngineLevel&& _Other) noexcept = delete;
	EngineLevel& operator=(const EngineLevel& _Other) = delete;
	EngineLevel& operator=(EngineLevel&& _Other) noexcept = delete;

protected:
	void Begin() override;
	void Tick(float DeltaTime) override;

private:

};