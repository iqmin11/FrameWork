#pragma once
#include "EngineNameTag.h"

// 설명 :
template <typename ResourceType>
class EngineResource : public EngineNameTag
{
private:
	static std::unordered_map<std::string, std::shared_ptr<ResourceType>> NamedResources;
	static std::vector<std::shared_ptr<ResourceType>> UnnamedResources;

public:
	// constrcuter destructer
	EngineResource() = default;
	virtual ~EngineResource() = 0 {};

	// delete Function
	EngineResource(const EngineResource& _Other) = delete;
	EngineResource(EngineResource&& _Other) noexcept = delete;
	EngineResource& operator=(const EngineResource& _Other) = delete;
	EngineResource& operator=(EngineResource&& _Other) noexcept = delete;

	static std::shared_ptr<ResourceType> Find(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpper(_Name);

		auto FindIter = NamedResources.find(UpperName);
		if (FindIter == NamedResources.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

	virtual void Setting() {};

protected:

	static std::shared_ptr<ResourceType> CreateInst(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpper(_Name);

		if (Find(UpperName) != nullptr)
		{
			MsgAssert("이미 존재하는 리소스입니다");
		}

		std::shared_ptr<ResourceType> NewInst = std::make_shared<ResourceType>();
		NewInst->SetName(UpperName);
		
		NamedResources.insert(std::make_pair(UpperName, NewInst));
		return NewInst;
	}

	static std::shared_ptr<ResourceType> CreateInst()
	{
		std::shared_ptr<ResourceType> NewInst = std::make_shared<ResourceType>();
		UnnamedResources.emplace_back(NewInst);
		return NewInst;
	}

private:
	std::string Path;
};

template <typename ResourceType>
std::unordered_map<std::string, std::shared_ptr<ResourceType>> EngineResource<ResourceType>::NamedResources;

template <typename ResourceType>
std::vector<std::shared_ptr<ResourceType>> EngineResource<ResourceType>::UnnamedResources;
