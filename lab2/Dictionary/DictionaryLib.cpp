#include "DictionaryLib.h"

std::optional<Translations> LookupTranslation(const Dictionary& dictionary, const std::string& phrase)
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

void AddDirectTranslations(Dictionary& dictionary, const std::string& phrase, const Translations& translations)
{
	auto const sourceInLower = ToLower(phrase);
	auto it = dictionary.find(sourceInLower);
	if (it == dictionary.end())
	{
		dictionary[sourceInLower] = translations;
	}
	else
	{
		it->second.insert(translations.begin(), translations.end());
	}
}

void AddReverseTranslations(Dictionary& dictionary, const Translations& translations, const std::string& phrase)
{
	for (auto const& translation : translations)
	{
		auto const translationInLower = ToLower(translation);
		auto it = dictionary.find(translationInLower);
		if (it == dictionary.end())
		{
			dictionary[translationInLower] = { phrase };
		}
		else
		{
			it->second.insert(phrase);
		}
	}
}

void AddTranslations(Dictionary& dictionary, const std::string& phrase, const Translations& translations)
{
	AddDirectTranslations(dictionary, phrase, translations);
	AddReverseTranslations(dictionary, translations, phrase);
}

void AddTranslations(Dictionary& dictionary, const std::string& phrase, const std::string& translationsString)
{
	auto const translations = StringToSet(translationsString, DELIMITER);
	if (translations.empty())
	{
		throw std::invalid_argument("empty translation");
	}

	AddTranslations(dictionary, phrase, translations);
}
