#pragma once
#include "EngineBase/EnginePath.h"
#include "EngineNameTag.h"
#include "EngineDevice.h"

// ���� :
//typedef int ResorceType;
template <typename ResorceType>
class EngineResorce : public EngineNameTag
{
public:
	// constrcuter destructer
	EngineResorce() {};
	virtual ~EngineResorce() = 0 {};

	// delete Function
	EngineResorce(const EngineResorce& _Other) = delete;
	EngineResorce(EngineResorce&& _Other) noexcept = delete;
	EngineResorce& operator=(const EngineResorce& _Other) = delete;
	EngineResorce& operator=(EngineResorce&& _Other) noexcept = delete;

	void SetPath(const EnginePath& ResorcePath)
	{
		Path = ResorcePath;
	}

	const EnginePath& GetPath()
	{
		return Path;
	}

	static std::shared_ptr<ResorceType> Find(std::string_view ResorceName)
	{
		std::string UpperName = EngineString::ToUpper(ResorceName);
		auto FindIter = ResorcesContainer.find(UpperName);

		if (FindIter != ResorcesContainer.end())
		{
			return FindIter->second;
		}

		assert("ã�����ϴ� ���ҽ��� �������� �ʽ��ϴ�.");
		return nullptr;
	}

	static void ResorcesClear()
	{
		ResorcesContainer.clear();
	}

protected:

	static std::shared_ptr<ResorceType> Create(std::string_view ResorceName)
	{
		std::string UpperName = EngineString::ToUpper(ResorceName);

		if (Find(UpperName) != nullptr)
		{
			assert("�ߺ� �̸��� ���� ���ҽ��� �̹� �����մϴ�");
			return nullptr;
		}

		std::shared_ptr<ResorceType> NewResorce = std::make_shared<ResorceType>();

		ResorcesContainer.insert(std::make_pair(UpperName, NewResorce));

		return NewResorce;
	}

private:
	EnginePath Path;
	static std::unordered_map<std::string, std::shared_ptr<ResorceType>> ResorcesContainer;

};

template <typename ResorceType>
std::unordered_map<std::string, std::shared_ptr<ResorceType>> EngineResorce<ResorceType>::ResorcesContainer;

