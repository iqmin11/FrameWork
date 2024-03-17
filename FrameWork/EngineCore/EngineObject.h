#pragma once
class EngineObject
{
public:
	// construtor destructor
	EngineObject();
	virtual ~EngineObject();

	// delete Function
	EngineObject(const EngineObject& _Other) = delete;
	EngineObject(EngineObject&& _Other) noexcept = delete;
	EngineObject& operator=(const EngineObject& _Other) = delete;
	EngineObject& operator=(EngineObject&& _Other) noexcept = delete;

protected:

	virtual void Begin() = 0;
	virtual void Tick(float DeltaTime) = 0;

private:

};

