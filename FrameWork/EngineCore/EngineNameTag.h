#pragma once

// Ό³Έν :
class EngineNameTag
{
public:
	// constrcuter destructer
	EngineNameTag();
	~EngineNameTag();

	// delete Function
	EngineNameTag(const EngineNameTag& _Other) = delete;
	EngineNameTag(EngineNameTag&& _Other) noexcept = delete;
	EngineNameTag& operator=(const EngineNameTag& _Other) = delete;
	EngineNameTag& operator=(EngineNameTag&& _Other) noexcept = delete;

	void SetName(std::string_view SettingName)
	{
		Name = SettingName;
	}

	std::string GetName()
	{
		return Name;
	}

	std::string_view GetNameView()
	{
		return Name;
	}

protected:

private:
	std::string Name = "";

};

