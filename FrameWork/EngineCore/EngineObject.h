#pragma once
class EngineObject : public std::enable_shared_from_this<EngineObject>
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
	virtual void Tick(float DeltaTime) {};

private:
	std::string Name = "";
};

