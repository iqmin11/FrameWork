#pragma once
#include "EngineCore/EngineLevel.h"

// Ό³Έν :
class ChatLevel : public EngineLevel
{
public:
	// constrcuter destructer
	ChatLevel();
	~ChatLevel();

	// delete Function
	ChatLevel(const ChatLevel& _Other) = delete;
	ChatLevel(ChatLevel&& _Other) noexcept = delete;
	ChatLevel& operator=(const ChatLevel& _Other) = delete;
	ChatLevel& operator=(ChatLevel&& _Other) noexcept = delete;

protected:
	void Begin() override;
	void Tick(float DeltaTime) override;

private:
};

