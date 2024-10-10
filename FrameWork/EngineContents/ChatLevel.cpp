#include "PrecompileHeader.h"
#include "ChatLevel.h"
#include "EngineCore/EngineGUI.h"
#include "ChatGUI.h"
#include "NetworkGUI.h"
#include "ChatUser.h"

ChatLevel::ChatLevel() 
{
}

ChatLevel::~ChatLevel() 
{
}

void ChatLevel::Begin()
{
	EngineGUI::GUIWindowCreate<ChatGUI>("Chat");
	EngineGUI::GUIWindowCreate<NetworkGUI>("Net");

	CreateActor<ChatUser>();
}

void ChatLevel::Tick(float DeltaTime)
{
	EngineLevel::Tick(DeltaTime);
}

