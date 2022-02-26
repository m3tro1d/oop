#include "DictionaryLib.h"

std::string ToLower(const std::string& string)
{
	std::string result;
	std::transform(
		string.begin(),
		string.end(),
		std::back_inserter(result),
		[](char ch) {
			return std::tolower(ch);
		});

	return result;
}

void AddTranslation(Dictionary& dictionary, const std::string& phrase, const std::string& translation)
{
	dictionary[ToLower(phrase)] = translation;
}

std::optional<std::string> LookupTranslation(const Dictionary& dictionary, const std::string& phrase)
{
	try
	{
		return dictionary.at(ToLower(phrase));
	}
	catch (const std::out_of_range&)
	{
		return std::nullopt;
	}
}
