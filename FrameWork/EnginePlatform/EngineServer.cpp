#include "PrecompileHeader.h"
#include "EngineServer.h"

EngineServer::EngineServer() 
{
}

EngineServer::~EngineServer() 
{
}

void EngineServer::ServerOpen(short _Port, int _BackLog)
{
	WSAData WsaData;
	int ErrorCode = WSAStartup(MAKEWORD(2, 2), &WsaData);

	if (ErrorCode == SOCKET_ERROR)
	{
		MsgAssert("socket Error");
		return;
	}

	SOCKADDR_IN Add;
	Add.sin_family = AF_INET; // ip4주소 체계를 쓰겠다.
	Add.sin_port = htons(_Port); // 네트워크 통신에 유효한 에디안 방식으로 만들어준다.

	if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Add.sin_addr))
	{
		return;
	}

	AcceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == AcceptSocket)
	{
		return;
	}

	if (SOCKET_ERROR == bind(AcceptSocket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
	{
		return;
	}

	BackLog = _BackLog;

	if (SOCKET_ERROR == listen(AcceptSocket, _BackLog))
	{
		return;
	}

	ServerThread.Start("AcceptFunction", std::bind(EngineServer::AcceptThread, AcceptSocket, this));
}

void EngineServer::Send(void* SendData, unsigned int Size)
{
	int a = 0;
}

void EngineServer::AcceptThread(SOCKET _AcceptSocket, EngineServer* _Net)
{
	int a = 0;
}

