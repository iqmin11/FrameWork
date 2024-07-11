#pragma once
#include "EngineBase/EngineSerializer.h"
#include <memory>

// 설명 :
class EnginePacket : public std::enable_shared_from_this<EnginePacket>
{
public:
	// constrcuter destructer
	EnginePacket();
	~EnginePacket();

	// delete Function
	EnginePacket(const EnginePacket& _Other) = delete;
	EnginePacket(EnginePacket&& _Other) noexcept = delete;
	EnginePacket& operator=(const EnginePacket& _Other) = delete;
	EnginePacket& operator=(EnginePacket&& _Other) noexcept = delete;

protected:

private:
	unsigned int PacketID = -1; // <= 종류인데 int로 처리한다.
	unsigned int Size = -1; // <= 패킷의 크기
	unsigned int ObjectID = -1; // <= 어떤 오브젝트가 보냈다.

};

