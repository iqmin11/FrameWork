#include "PrecompileHeader.h"
#include "EngineString.h"

std::string EngineString::ToUpper(std::string_view Str)
{
	std::string result = Str.data();
	for (size_t i = 0; i < result.length(); i++)
	{
		result[i] = toupper(result[i]);
	}

	return result;
}

std::wstring EngineString::AsciiToUnicode(const std::string& Str)
{
	int size_needed = MultiByteToWideChar(CP_ACP, 0, Str.c_str(), (int)Str.size(), NULL, 0);
	std::wstring WName(size_needed, 0);
	::MultiByteToWideChar(CP_ACP, 0, Str.c_str(), (int)Str.size(), &WName[0], size_needed);
	return WName;
}
