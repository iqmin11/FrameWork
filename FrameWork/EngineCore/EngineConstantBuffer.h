#pragma once
#include "EngineResorce.h"
#include "EngineDirectBuffer.h"

struct Constants
{
	float4 Pos;
	float4 Color;
};

// Ό³Έν :
class EngineConstantBuffer : public EngineResorce<EngineConstantBuffer>, public EngineDirectBuffer
{
public:
	// constrcuter destructer
	EngineConstantBuffer();
	~EngineConstantBuffer();

	// delete Function
	EngineConstantBuffer(const EngineConstantBuffer& _Other) = delete;
	EngineConstantBuffer(EngineConstantBuffer&& _Other) noexcept = delete;
	EngineConstantBuffer& operator=(const EngineConstantBuffer& _Other) = delete;
	EngineConstantBuffer& operator=(EngineConstantBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<EngineConstantBuffer> Load(std::string_view ConstantBufferName);

	void SetData(const void* Data, UINT Size);

protected:

private:

};

