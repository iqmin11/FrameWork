#pragma once
#include "EngineResorce.h"
#include "EngineVertex.h"
#include "EngineDirectBuffer.h"

// ���� :
//typedef EngineVertex VertexType;
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
		std::shared_ptr<EngineVertexBuffer> NewVBuffer = Create(Name);
		NewVBuffer->LayOutInfo = VertexType::LayOutInfo.GetDescs().data();

		NewVBuffer->Stride = sizeof(VertexType);
		NewVBuffer->NumVerts = static_cast<UINT>(VertexData.size());
		NewVBuffer->Offset = 0;

		NewVBuffer->BufferDesc.ByteWidth = NewVBuffer->Stride * NewVBuffer->NumVerts;
		NewVBuffer->BufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		NewVBuffer->BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA VertexSubresourceData = { VertexData.data() };

		HRESULT Result = EngineDevice::GetDevice()->CreateBuffer(&(NewVBuffer->BufferDesc), &VertexSubresourceData, &(NewVBuffer->Buffer));
		assert(SUCCEEDED(Result));

		return NewVBuffer;
	}

	UINT GetStride() const
	{
		return Stride;
	}

	UINT GetNumVerts() const
	{
		return NumVerts;
	}

	UINT GetOffset() const
	{
		return Offset;
	}

	void Setting() override;

protected:

private:
	D3D11_INPUT_ELEMENT_DESC* LayOutInfo = nullptr;
	
	UINT Stride = 0;
	UINT NumVerts = 0;
	UINT Offset = 0;
};

