#include "PrecompileHeader.h"
#include "EnginePath.h"

#include "EngineDebug.h"

EnginePath::EnginePath()
	: Path(std::filesystem::current_path())
{
}

EnginePath::EnginePath(std::filesystem::path _Path)
	: Path(_Path)
{
}

EnginePath::EnginePath(const std::string& _Path)
	: Path(_Path)
{
}

EnginePath::~EnginePath() 
{
}

EnginePath::EnginePath(const EnginePath& _Other)
	: Path(_Other.Path)
{

}

EnginePath::EnginePath(EnginePath&& _Other) noexcept
	: Path(std::move(_Other.Path))
{

}

std::string EnginePath::GetFileName(std::string_view _Path)
{
	std::filesystem::path NewPath = _Path;
	return NewPath.filename().string();
}

std::string EnginePath::GetFolderPath(std::string_view _Path)
{
	size_t FileNameSize = GetFileName(_Path).size();
	std::string FullPath = _Path.data();

	FullPath = FullPath.replace(FullPath.size() - FileNameSize, FileNameSize, "");
	return FullPath;
}

std::string EnginePath::GetFileName() const
{
	return Path.filename().string();
}

std::string EnginePath::GetFullPath() const
{
	return Path.string();
}

std::string EnginePath::GetExtension() const
{
	return Path.extension().string();
}

void EnginePath::MoveParent()
{
	Path = Path.parent_path();
}

void EnginePath::MoveParentToChildPath(std::string_view _String)
{
	while (!IsRoot())
	{
		if (IsExistsToPlusString(_String))
		{
			return;
		}

		MoveParent();
	}

	MsgAssert("�̷� ��θ� �ڽ����� ���� �θ�� �������� �ʽ��ϴ�.");
}

bool EnginePath::IsExists()
{
	return std::filesystem::exists(Path);
}

bool EnginePath::IsExistsToPlusString(std::string_view _String)
{
	std::filesystem::path NewPath = Path / std::filesystem::path(_String);
	return std::filesystem::exists(NewPath);
}

bool EnginePath::IsDirectory() const
{
	return std::filesystem::is_directory(Path);
}

bool EnginePath::IsRoot()
{
	return Path.root_path() == Path;
}

bool EnginePath::TryMove(std::string_view _Path)
{
	Path /= std::filesystem::path(_Path);
	
	if(IsExists())
	{
		return false;
	}

	return true;
}

void EnginePath::SetPath(std::string_view _Path)
{
	Path = _Path;
}


