#include "PrecompileHeader.h"
#include "ChatLevel.h"
#include "EngineCore/EngineGUI.h"
#include "ChatGUI.h"

ChatLevel::ChatLevel() 
{
}

ChatLevel::~ChatLevel() 
{
}

void ChatLevel::Begin()
{
	EngineGUI::GUIWindowCreate<ChatGUI>("Chat");
}

void ChatLevel::Tick(float DeltaTime)
{
	EngineLevel::Tick(DeltaTime);
}

