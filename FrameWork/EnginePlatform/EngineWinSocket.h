#pragma once

// Ό³Έν :
class EngineWinSocket
{
public:
	// constrcuter destructer
	EngineWinSocket();
	~EngineWinSocket();

	// delete Function
	EngineWinSocket(const EngineWinSocket& _Other) = delete;
	EngineWinSocket(EngineWinSocket&& _Other) noexcept = delete;
	EngineWinSocket& operator=(const EngineWinSocket& _Other) = delete;
	EngineWinSocket& operator=(EngineWinSocket&& _Other) noexcept = delete;

	void Initialize();

protected:

private:

};

