#pragma once

// ���� :
class EngineNetwork
{
public:
	// constrcuter destructer
	EngineNetwork();
	~EngineNetwork();

	// delete Function
	EngineNetwork(const EngineNetwork& _Other) = delete;
	EngineNetwork(EngineNetwork&& _Other) noexcept = delete;
	EngineNetwork& operator=(const EngineNetwork& _Other) = delete;
	EngineNetwork& operator=(EngineNetwork&& _Other) noexcept = delete;

	virtual void Send(void* SendData, unsigned int Size) = 0;

	inline bool IsNet() const
	{
		return IsNetValue;
	}

protected:
	static void ReciveThreadFunction(SOCKET Socket, EngineNetwork* Net);

private:
	std::atomic<bool> IsNetValue = true;
};

