#pragma once
#include "EngineNetwork.h"
#include "EngineThread.h"

// Ό³Έν :
class EngineClient : public EngineNetwork
{
public:
	// constrcuter destructer
	EngineClient();
	~EngineClient();

	// delete Function
	EngineClient(const EngineClient& _Other) = delete;
	EngineClient(EngineClient&& _Other) noexcept = delete;
	EngineClient& operator=(const EngineClient& _Other) = delete;
	EngineClient& operator=(EngineClient&& _Other) noexcept = delete;

	bool Connect(const std::string& _IP, unsigned short _Port);

protected:
	void Send(void* Data, unsigned int Size) override;

private:
	EngineThread ReciveThread;
	SOCKET ClientSocket;
};

