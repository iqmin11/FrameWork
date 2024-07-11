#include "PrecompileHeader.h"
#include "EngineClient.h"

EngineClient::EngineClient() 
{
}

EngineClient::~EngineClient() 
{
}

bool EngineClient::Connect(const std::string& _IP, unsigned short _Port)
{
	WSAData WsaData;

    int errorCode = WSAStartup(MAKEWORD(2, 2), &WsaData);
    if (SOCKET_ERROR == errorCode)
    {
        MsgAssert("socket Error");
        return false;
    }

    ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET == ClientSocket)
    {
        return false;
    }

    SOCKADDR_IN ClientAdd;

    ClientAdd.sin_family = AF_INET;
    ClientAdd.sin_port = htons(30000);

    std::string IP = _IP;

    if (SOCKET_ERROR == inet_pton(AF_INET, IP.c_str(), &ClientAdd.sin_addr))
    {
        return false;
    }

    int Len = sizeof(SOCKADDR_IN);

    // 접속 시간을 초과했습니다.
    if (SOCKET_ERROR == connect(ClientSocket, (const sockaddr*)&ClientAdd, Len))
    {
        MsgAssert("Fail Connect");
        return false;
    }

    ReciveThread.Start("Client Recv Thread", std::bind(&EngineNetwork::ReciveThreadFunction, ClientSocket, this));

    return true;
}

void EngineClient::Send(void* Data, unsigned int Size)
{
}

