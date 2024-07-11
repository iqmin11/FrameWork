#include "PrecompileHeader.h"
#include "EngineServer.h"

EngineServer::EngineServer() 
{
}

EngineServer::~EngineServer() 
{
	if (AcceptSocket != 0)
	{
		closesocket(AcceptSocket);
	}
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

	AcceptThread.Start("AcceptFunction", std::bind(EngineServer::AcceptThreadFunc, AcceptSocket, this));
}

void EngineServer::Send(const char* SendData, unsigned int Size)
{
	for (auto User : Users)
	{
		::send(User.second, SendData, Size, 0);
	}
}

void EngineServer::AcceptThreadFunc(SOCKET _AcceptSocket, EngineServer* _Net)
{
	int AddressLen = sizeof(SOCKADDR_IN);
	while (true == _Net->IsNet())
	{
		SOCKADDR_IN ClientAdd;

		memset(&ClientAdd, 0, sizeof(ClientAdd));

		SOCKET CientSocket = accept(_AcceptSocket, (sockaddr*)&ClientAdd, &AddressLen);

		if (SOCKET_ERROR == CientSocket || INVALID_SOCKET == CientSocket)
		{
			return;
		}

		// 이 유저가 접속했을때 꼭 해야할께 있을 가능성이 높은데.

		std::shared_ptr<EngineThread> NewThread = std::make_shared<EngineThread>();
		_Net->ReciveThreads.push_back(NewThread);

		std::string ThreadName = std::to_string(CientSocket);
		ThreadName += "Server Recv Thread";

		_Net->AccpetCallBack(CientSocket, _Net);

		NewThread->Start(ThreadName, std::bind(&EngineNetwork::ReciveThreadFunction, CientSocket, _Net));
	}
}

