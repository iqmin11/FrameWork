#include "PrecompileHeader.h"
#include "EngineNetwork.h"
#include "EngineBase/EngineSerializer.h"

EngineNetwork::EngineNetwork() 
{
}

EngineNetwork::~EngineNetwork() 
{
	IsNetValue = false;
}

void EngineNetwork::ReciveThreadFunction(SOCKET Socket, EngineNetwork* Net)
{
	char Buffer[1024] = { 0 };
	EngineSerializer Serializer;

	int PacketType = -1;
	int PacketSize = -1;

	while (Net->IsNet())
	{
		int Result = ::recv(Socket, Buffer, sizeof(Buffer), 0);

		if (Result == -1)
		{
			return;
		}
	}
}

