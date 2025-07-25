#pragma once

#include <EnginePlatform/EngineWindow.h>

class EngineLevel;
class EngineCore
{
public:
	// construtor destructor
	EngineCore();
	~EngineCore();

	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	static void CoreInit(HINSTANCE hInst,
		std::string_view TitleName, 
		std::function<void()> Begin, 
		std::function<void()> End, 
		const float4& WindowPos = EngineWindow::DefaultWindowPos,
		const float4& WindowSize = EngineWindow::DefaultWindowSize);

	static void CoreTick();

	template <typename LevelType>
	static std::shared_ptr<LevelType> CreateLevel(std::string_view LevelName = "")
	{
		std::shared_ptr<EngineLevel> NewLevel = std::make_shared<LevelType>();
		std::string Name = LevelName.data();

		if (Name == "")
		{
			const type_info& TypeInfo = typeid(LevelType);
			Name = TypeInfo.name();
			Name.replace(0, 6, "");
		}

		Name = EngineString::ToUpper(Name);

		auto InsertResult = Levels.insert(std::make_pair(Name, NewLevel));
		if (!InsertResult.second)
		{
			MsgAssert("이미 있는 이름의 레벨은 추가할 수 없습니다")
			return nullptr;
		}

		NewLevel->Init_Internal(NewLevel);
		NewLevel->Begin();

		return std::dynamic_pointer_cast<LevelType>(NewLevel);
	}

	//Level Change Interface
	static void ChangeLevel(std::string_view LevelName)
	{
		std::string FindName = LevelName.data();
		FindName = EngineString::ToUpper(FindName);
		auto FindIter = Levels.find(FindName);

		if (FindIter == Levels.end())
		{
			MsgAssert("찾고자 하는 레벨이 없습니다");
		}

		ChangeRequestLevel = FindIter->second;
	}

protected:


private:

	//EngineCoreBase
	static std::shared_ptr<EngineLevel> CurUpdatedLevel;

	static void EngineBegin(std::function<void()> ContentsBegin = nullptr);
	static void EngineEnd(std::function<void()> ContentsEnd = nullptr);

	static std::map<std::string, std::shared_ptr<EngineLevel>> Levels;

	//Change Level
	static std::shared_ptr<EngineLevel> ChangeRequestLevel;

	static bool HasLevelChanged();
	static void LevelChangeProc();
	static void CoreResourceInit();
	static void CoreResourceRelease();

};

