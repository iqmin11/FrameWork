#include "PrecompileHeader.h"
#include "EngineDirectBuffer.h"

EngineDirectBuffer::EngineDirectBuffer() 
{
}

EngineDirectBuffer::~EngineDirectBuffer() 
{
	if (Buffer != nullptr)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}

