#include "PrecompileHeader.h"
#include "EngineSerializer.h"

EngineSerializer::EngineSerializer() 
{
	Buffer.resize(1024);
}

EngineSerializer::~EngineSerializer() 
{
}

void EngineSerializer::Write(const void* SorceData, unsigned int Size)
{
	if (WriteOffset + Size >= Buffer.size())
	{
		Buffer.resize(Buffer.capacity() * 2);
	}

	::memcpy_s(&Buffer[WriteOffset], Size, SorceData, Size);
	WriteOffset += Size;
}

void EngineSerializer::Read(void* DestData, unsigned int Size)
{
	::memcpy_s(DestData, Size, &Buffer[ReadOffset], Size);
	ReadOffset += Size;
}


