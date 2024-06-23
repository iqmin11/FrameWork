#include "PrecompileHeader.h"
#include "EngineWinSocket.h"

EngineWinSocket::EngineWinSocket() 
{
}

EngineWinSocket::~EngineWinSocket() 
{
}

void EngineWinSocket::Initialize()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0)
	{
		MsgAssert("WSAStartup Failed");
	}
}

