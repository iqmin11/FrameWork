#pragma once
#include "EnginePath.h"

// Ό³Έν :
class EngineFile;
class EngineDirectory : public EnginePath
{
public:
	// constrcuter destructer
	EngineDirectory();
	~EngineDirectory();

	EngineDirectory(std::string_view Path);
	EngineDirectory(std::filesystem::path Path);
	
	// delete Function
	EngineDirectory(const EngineDirectory& _Other) = delete;
	EngineDirectory(EngineDirectory&& _Other) noexcept
		:EnginePath(std::move(_Other))
	{

	}
	EngineDirectory& operator=(const EngineDirectory& _Other) = delete;
	EngineDirectory& operator=(EngineDirectory&& _Other) noexcept = delete;

	void MoveParentToDirectory(std::string_view _String);

	EnginePath GetPlusFileName(std::string_view _FileName);

protected:

private:

};

