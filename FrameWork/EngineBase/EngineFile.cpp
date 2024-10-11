#include "PrecompileHeader.h"
#include "EngineFile.h"

#include "EngineDebug.h"

EngineFile::EngineFile() 
{
}

EngineFile::~EngineFile() 
{
}

EngineFile::EngineFile(std::filesystem::path _Path)
	: EnginePath(_Path)
{
}

EngineFile::EngineFile(std::string_view _Path)
	: EnginePath(_Path)
{
}

EngineFile::EngineFile(const EnginePath& _Path)
	: EnginePath(_Path)
{
}

EngineDirectory EngineFile::GetDirectory()
{
	EngineDirectory ReturnPath = Path;
	ReturnPath.TryMoveParent();
	return ReturnPath;
}
