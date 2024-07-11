#pragma once
#include "EngineCore/EngineGUI.h"

// Ό³Έν :
class NetworkGUI : public EngineGUIWindow
{
public:
	// constrcuter destructer
	NetworkGUI();
	~NetworkGUI();

	// delete Function
	NetworkGUI(const NetworkGUI& _Other) = delete;
	NetworkGUI(NetworkGUI&& _Other) noexcept = delete;
	NetworkGUI& operator=(const NetworkGUI& _Other) = delete;
	NetworkGUI& operator=(NetworkGUI&& _Other) noexcept = delete;

protected:
	void Begin() override;
	void Tick(float DeltaTime) override;


private:

	bool IsServer;
	std::string IP = "127.0.0.1";
	int Port = 30000;
	bool IsClient;
	std::string TestSendBuffer = "fashdjklfhajklfhasdjfhaklfhafhasd";
};

