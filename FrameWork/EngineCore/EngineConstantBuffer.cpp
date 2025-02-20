#include "PrecompileHeader.h"
#include "EngineConstantBuffer.h"

EngineConstantBuffer::EngineConstantBuffer()
{
}

EngineConstantBuffer::~EngineConstantBuffer()
{
}

std::shared_ptr<EngineConstantBuffer> EngineConstantBuffer::Load(std::string_view ConstantBufferName)
{
	std::shared_ptr<EngineConstantBuffer> NewCb = Create(ConstantBufferName);

	// Create Constant Buffer
	// ByteWidth must be a multiple of 16, per the docs
	NewCb->BufferDesc.ByteWidth = sizeof(Constants) + 0xf & 0xfffffff0;
	NewCb->BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	NewCb->BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	NewCb->BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hResult = EngineDevice::GetDevice()->CreateBuffer(&NewCb->BufferDesc, nullptr, &NewCb->Buffer);
	assert(SUCCEEDED(hResult));

	return NewCb;
}

void EngineConstantBuffer::SetData(const void* Data, UINT Size)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	EngineDevice::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	Constants* constants = (Constants*)(mappedSubresource.pData);
	constants->Pos = { 0.25f, 0.3f, 0.0f, 0.0f };
	constants->Color = { 0.7f, 0.65f, 0.1f, 1.f };
	EngineDevice::GetContext()->Unmap(Buffer, 0);
}

