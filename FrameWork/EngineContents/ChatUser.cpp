#include "PrecompileHeader.h"
#include "ChatUser.h"

ChatUser* ChatUser::MainChatUser = nullptr;

ChatUser::ChatUser()
{
	MainChatUser = this;
}

ChatUser::~ChatUser() 
{
}

void ChatUser::Begin()
{
	int a = 0;
}

void ChatUser::Tick(float DeltaTime)
{
	NetControllType Type = GetControllType();

	switch (Type)
	{
	case NetControllType::None:
		UserTick(DeltaTime);
		break;
	case NetControllType::UserControll:
		UserTick(DeltaTime);
		break;
	case NetControllType::ServerControll:
		ServerTick(DeltaTime);
		break;
	default:
		break;
	}
}

void ChatUser::ServerTick(float DeltaTime)
{
	int a = 0;
}

void ChatUser::UserTick(float DeltaTime)
{
	int a = 0;
}

