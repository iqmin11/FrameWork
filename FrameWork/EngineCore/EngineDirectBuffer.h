#pragma once

// Ό³Έν :
class EngineDirectBuffer
{
public:
	// constrcuter destructer
	EngineDirectBuffer();
	~EngineDirectBuffer();

	// delete Function
	EngineDirectBuffer(const EngineDirectBuffer& _Other) = delete;
	EngineDirectBuffer(EngineDirectBuffer&& _Other) noexcept = delete;
	EngineDirectBuffer& operator=(const EngineDirectBuffer& _Other) = delete;
	EngineDirectBuffer& operator=(EngineDirectBuffer&& _Other) noexcept = delete;

	UINT GetBufferSize()
	{
		return BufferDesc.ByteWidth;
	}

protected:
	D3D11_BUFFER_DESC BufferDesc = {};
	ID3D11Buffer* Buffer = nullptr;

private:
};

