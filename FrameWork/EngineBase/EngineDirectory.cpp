#include "PrecompileHeader.h"
#include "EngineDirectory.h"

EngineDirectory::EngineDirectory() 
{
}

EngineDirectory::~EngineDirectory() 
{
}

EngineDirectory::EngineDirectory(std::string_view Path)
	: EnginePath(Path)

{
}

EngineDirectory::EngineDirectory(std::filesystem::path Path)
	: EnginePath(Path)
{

}

void EngineDirectory::MoveParentToDirectory(std::string_view _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	MoveParentToChildPath(MovePath.c_str());
}

EnginePath EngineDirectory::GetPlusFileName(std::string_view _FileName)
{
	return EnginePath(Path / std::filesystem::path(_FileName));
}