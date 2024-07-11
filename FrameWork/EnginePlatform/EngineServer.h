#pragma once
#include "EngineNetwork.h"

// Ό³Έν :
class EngineServer : public EngineNetwork
{
public:
	// constrcuter destructer
	EngineServer();
	~EngineServer();

	// delete Function
	EngineServer(const EngineServer& _Other) = delete;
	EngineServer(EngineServer&& _Other) noexcept = delete;
	EngineServer& operator=(const EngineServer& _Other) = delete;
	EngineServer& operator=(EngineServer&& _Other) noexcept = delete;

protected:

private:

};

