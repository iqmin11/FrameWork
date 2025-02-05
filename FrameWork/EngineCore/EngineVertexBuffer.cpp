#include "PrecompileHeader.h"
#include "EngineVertexBuffer.h"

#include "EngineDevice.h"

EngineVertexBuffer::EngineVertexBuffer() 
{
}

EngineVertexBuffer::~EngineVertexBuffer() 
{
	if (LayOutInfo != nullptr)
	{
		LayOutInfo = nullptr;
	}
}

void EngineVertexBuffer::Setting()
{
	EngineDevice::GetContext()->IASetVertexBuffers(0, 1, &Buffer, &Stride, &Offset);
}

