#pragma once
#include "EngineCore/EngineGUI.h"

// Ό³Έν :
class ChatGUI : public EngineGUIWindow
{
public:
	// constrcuter destructer
	ChatGUI();
	~ChatGUI();

	// delete Function
	ChatGUI(const ChatGUI& _Other) = delete;
	ChatGUI(ChatGUI&& _Other) noexcept = delete;
	ChatGUI& operator=(const ChatGUI& _Other) = delete;
	ChatGUI& operator=(ChatGUI&& _Other) noexcept = delete;

protected:
	void Begin() override;
	void Tick(float DeltaTime) override;
private:

};

