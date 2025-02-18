#pragma once
#include <filesystem>

class EnginePath
{
public:
	// constrcuter destructer
	EnginePath();
	EnginePath(std::filesystem::path _Path);
	EnginePath(const std::string& _Path);
	virtual ~EnginePath();

	// delete Function
	EnginePath(const EnginePath& _Other);
	EnginePath(EnginePath&& _Other) noexcept;
	EnginePath& operator=(const EnginePath& _Other);
	EnginePath& operator=(EnginePath&& _Other) noexcept;

	static std::string GetFileName(std::string_view _Path);
	static std::string GetFolderPath(std::string_view _Path);

	std::string GetFileName() const;
	std::string GetFullPathToString() const
	{
		return Path.string();
	}

	std::wstring GetFullPathToWstring() const
	{
		return Path.wstring();
	}

	std::string GetExtension() const;

	virtual bool TryMoveParent();

	// 내자식중 특정 경로나 특정 파일이 있는곳까지 자동 move
	void MoveParentToChildPath(std::string_view _String);

	bool IsExists();
	bool IsExistsToPlusString(std::string_view _String);

	// bool MoveParentToChildPath(const std::string_view& _IOName );

	bool IsDirectory() const;

	bool IsRoot();

	bool TryMove(std::string_view _Path);

	void SetPath(std::string_view _Path);



protected:

	std::filesystem::path Path;

};

