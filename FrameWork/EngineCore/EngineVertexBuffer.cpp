#include "PrecompileHeader.h"
#include "EngineVertexBuffer.h"

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

