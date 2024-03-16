#pragma once
class EngineDebug
{
public:
	// construtor destructor
	EngineDebug();
	~EngineDebug();

	// delete Function
	EngineDebug(const EngineDebug& _Other) = delete;
	EngineDebug(EngineDebug&& _Other) noexcept = delete;
	EngineDebug& operator=(const EngineDebug& _Other) = delete;
	EngineDebug& operator=(EngineDebug&& _Other) noexcept = delete;

protected:


private:

};

