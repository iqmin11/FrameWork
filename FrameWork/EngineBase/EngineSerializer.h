#pragma once

// Ό³Έν :
class EngineSerializer
{
public:
	// constrcuter destructer
	EngineSerializer();
	~EngineSerializer();

	// delete Function
	EngineSerializer(const EngineSerializer& _Other) = delete;
	EngineSerializer(EngineSerializer&& _Other) noexcept = delete;
	EngineSerializer& operator=(const EngineSerializer& _Other) = delete;
	EngineSerializer& operator=(EngineSerializer&& _Other) noexcept = delete;

	void Write(const void* SorceData, unsigned int Size);
	void Read(void* DestData, unsigned int Size);

	const unsigned char* GetConstData() const
	{
		return &Buffer[0];
	}

	const unsigned int GetReadOffset() const
	{
		return ReadOffset;
	}

	const unsigned int GetWriteOffset() const
	{
		return WriteOffset;
	}

protected:

private:
	unsigned int WriteOffset = 0;
	unsigned int ReadOffset = 0;
	std::vector<unsigned char> Buffer;
};

