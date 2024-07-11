#pragma once
#include "EngineNetwork.h"
#include "EngineThread.h"

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

	void ServerOpen(short Port, int BackLog = 512);

	void SetAcceptCallback(std::function<void(SOCKET, EngineServer*)> CallbackFunc)
	{
		AccpetCallBack = CallbackFunc;
	}

protected:
	void Send(const char* SendData, unsigned int Size) override;

private:
	int BackLog = 512;
	SOCKET AcceptSocket = 0;

	EngineThread AcceptThread;
	std::vector<std::shared_ptr<EngineThread>> ReciveThreads;

	std::map<int, SOCKET> Users;

	std::function<void(SOCKET _AcceptSocket, EngineServer* _Net)> AccpetCallBack;

	static void AcceptThreadFunc(SOCKET _AcceptSocket, EngineServer* _Net);


};

