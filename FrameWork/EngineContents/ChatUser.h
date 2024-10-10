#pragma once
#include "EngineCore/EngineActor.h"
#include "EnginePlatform/EngineNetObject.h"

// Ό³Έν :
class ChatUser : public EngineActor, public EngineNetObject
{
public:
	static ChatUser* MainChatUser;

	// constrcuter destructer
	ChatUser();
	~ChatUser();

	// delete Function
	ChatUser(const ChatUser& _Other) = delete;
	ChatUser(ChatUser&& _Other) noexcept = delete;
	ChatUser& operator=(const ChatUser& _Other) = delete;
	ChatUser& operator=(ChatUser&& _Other) noexcept = delete;

protected:
	void Begin() override;
	void Tick(float DeltaTime) override;
	void ServerTick(float DeltaTime);
	void UserTick(float DeltaTime);


private:

};

