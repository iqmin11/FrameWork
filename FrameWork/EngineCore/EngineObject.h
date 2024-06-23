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

	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

	std::string_view GetName()
	{
		return Name.c_str();
	}
	
protected:

	virtual void Begin() = 0;
	virtual void Tick(float DeltaTime) = 0;

private:
	std::string Name = "";
};

