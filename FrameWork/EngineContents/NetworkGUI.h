#pragma once
#include "EngineCore/EngineGUI.h"
#include "EnginePlatform/EngineServer.h"
#include "EnginePlatform/EngineClient.h"

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
	void Tick(float DeltaTime, std::shared_ptr<class EngineLevel> CurLevel) override;

	void ServerInit(std::shared_ptr<class EngineLevel> CurLevel);

private:

	static EngineNetwork* NetInst;
	EngineServer Server;
	EngineClient Client;

	bool IsServer = false;
	std::string IP = "127.0.0.1";
	int Port = 30000;

	bool IsClient = false;
	std::string TestSendBuffer = "fashdjklfhajklfhasdjfhaklfhafhasd";
};

