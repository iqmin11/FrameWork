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

	void Send(void* SendData, unsigned int Size) override;

protected:

private:
	int BackLog = 512;
	SOCKET AcceptSocket = 0;

	EngineThread ServerThread;

	std::map<int, SOCKET> Users;

	static void AcceptThread(SOCKET _AcceptSocket, EngineServer* _Net);


};

