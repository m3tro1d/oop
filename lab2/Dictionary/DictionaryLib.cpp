#include "DictionaryLib.h"

void AddTranslation(Dictionary& dictionary, const std::string& phrase, const std::string& translation)
{
	dictionary[phrase] = translation;
}

std::optional<std::string> LookupTranslation(const Dictionary& dictionary, const std::string& phrase)
{
	try
	{
		return dictionary.at(phrase);
	}
	catch (const std::out_of_range&)
	{
		return std::nullopt;
	}
}
