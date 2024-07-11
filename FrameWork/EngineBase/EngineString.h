#pragma once
#include <string>
#include <string_view>

class EngineString
{
public:
	static std::string ToUpper(std::string_view Str);
	static std::wstring AsciiToUnicode(const std::string& Str);
};

