#pragma once
#include <filesystem>

class EnginePath
{
public:
	// constrcuter destructer
	EnginePath();
	EnginePath(std::filesystem::path _Path);
	EnginePath(const std::string& _Path);
	~EnginePath();

	// delete Function
	EnginePath(const EnginePath& _Other);
	EnginePath(EnginePath&& _Other) noexcept;
	EnginePath& operator=(const EnginePath& _Other) = delete;
	EnginePath& operator=(EnginePath&& _Other) noexcept = delete;

	static std::string GetFileName(std::string_view _Path);
	static std::string GetFolderPath(std::string_view _Path);

	std::string GetFileName() const;
	std::string GetFullPath() const;
	std::string GetExtension() const;

	void MoveParent();

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

private:
	// 고생고생해서 만들지 않게 되었습니다.
	// std::string Path;
	std::filesystem::path Path;

};

