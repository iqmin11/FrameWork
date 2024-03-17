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
