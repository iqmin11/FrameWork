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

	// ���ڽ��� Ư�� ��γ� Ư�� ������ �ִ°����� �ڵ� move
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
	// �������ؼ� ������ �ʰ� �Ǿ����ϴ�.
	// std::string Path;
	std::filesystem::path Path;

};

