#pragma once
#include "EnginePath.h"
#include "EngineDirectory.h"
#include "EngineSerializer.h"

// Ό³Έν :
class EngineFile : public EnginePath
{
public:
	// constrcuter destructer
	EngineFile();
	~EngineFile();
	EngineFile(std::filesystem::path _Path);
	EngineFile(std::string_view _Path);
	EngineFile(const EnginePath& _Path);

	// delete Function
	//EngineFile(const EngineFile& _Other) = delete;
	// EngineFile(EngineFile&& _Other) noexcept = delete;
	//EngineFile& operator=(const EngineFile& _Other) = delete;
	//EngineFile& operator=(EngineFile&& _Other) noexcept = delete;

	std::string GetFullPathToString()
	{
		return Path.string();
	}

	std::wstring GetFullPathToWstring()
	{
		return Path.wstring();
	}

	EngineDirectory GetDirectory();

protected:

private:

};

