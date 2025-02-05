#pragma once
#include "EngineResorce.h"
#include "EngineVertex.h"
#include "EngineDirectBuffer.h"

// Ό³Έν :
typedef int VertexType;
class EngineVertexBuffer : public EngineResorce<EngineVertexBuffer>, public EngineDirectBuffer
{
public:
	// constrcuter destructer
	EngineVertexBuffer();
	~EngineVertexBuffer();

	// delete Function
	EngineVertexBuffer(const EngineVertexBuffer& _Other) = delete;
	EngineVertexBuffer(EngineVertexBuffer&& _Other) noexcept = delete;
	EngineVertexBuffer& operator=(const EngineVertexBuffer& _Other) = delete;
	EngineVertexBuffer& operator=(EngineVertexBuffer&& _Other) noexcept = delete;

	template <typename VertexType>
	static std::shared_ptr<EngineVertexBuffer> Load(std::string_view Name, const std::vector<VertexType>& VertexData)
	{
		std::shared_ptr<EngineVertexBuffer> NewVBuffer = EngineResorce::Create(Name);
		NewVBuffer->LayOutInfo = VertexType::LayOutDesc;

		NewVBuffer->Stride = sizeof(VertexType);
		NewVBuffer->NumVerts = VertexData.size();
		NewVBuffer->Offset = 0;

		NewVBuffer->BufferDesc.ByteWidth = NewVBuffer->Stride * NewVBuffer->NumVerts;
		NewVBuffer->BufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		NewVBuffer->BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA VertexSubresourceData = { VertexData.data() };

		HRESULT Result = EngineDevice::GetDevice()->CreateBuffer(&(NewVBuffer->BufferDesc), &VertexSubresourceData, &(NewVBuffer->Buffer));
		assert(SUCCEEDED(Result));

		return NewVBuffer;
	}

	ID3D11Buffer* GetVb()
	{
		return Buffer;
	}

	UINT GetStride()
	{
		return Stride;
	}

	UINT GetNumVerts()
	{
		return NumVerts;
	}

	UINT GetOffset()
	{
		return Offset;
	}

protected:

private:
	D3D11_INPUT_ELEMENT_DESC* LayOutInfo = nullptr;
	
	UINT Stride = 0;
	UINT NumVerts = 0;
	UINT Offset = 0;
};

