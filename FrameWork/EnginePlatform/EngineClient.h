#pragma once

// Ό³Έν :
class EngineClient
{
public:
	// constrcuter destructer
	EngineClient();
	~EngineClient();

	// delete Function
	EngineClient(const EngineClient& _Other) = delete;
	EngineClient(EngineClient&& _Other) noexcept = delete;
	EngineClient& operator=(const EngineClient& _Other) = delete;
	EngineClient& operator=(EngineClient&& _Other) noexcept = delete;

protected:

private:

};

