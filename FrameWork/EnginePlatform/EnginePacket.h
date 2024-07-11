#pragma once
#include "EngineBase/EngineSerializer.h"
#include <memory>

// ���� :
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
	unsigned int PacketID = -1; // <= �����ε� int�� ó���Ѵ�.
	unsigned int Size = -1; // <= ��Ŷ�� ũ��
	unsigned int ObjectID = -1; // <= � ������Ʈ�� ���´�.

};

