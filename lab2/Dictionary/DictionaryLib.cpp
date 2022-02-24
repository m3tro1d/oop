#include "DictionaryLib.h"

std::string GetDictionaryPath(int argc, char** argv)
{
	if (argc != 2)
	{
		return DEFAULT_DICTIONARY_PATH;
	}

	return argv[1];
}

void LoadDictionary(const std::string& dictionaryFilename, Dictionary& dictionary)
{
	std::ifstream dictionaryFile(dictionaryFilename);
	if (!dictionaryFile.is_open())
	{
		return;
	}

	std::string line;
	while (std::getline(dictionaryFile, line))
	{
		std::string source;
		std::string translation;

		std::stringstream translationUnit(line);
		std::getline(translationUnit, source, ':');
		std::getline(translationUnit, translation);

		if (source.empty() || translation.empty())
		{
			throw std::invalid_argument("Invalid dictionary file format");
		}
	}

	dictionaryFile.close();
}

void SaveDictionary(const std::string& dictionaryFilename, const Dictionary& dictionary)
{
	std::ofstream dictionaryFile(dictionaryFilename);
	if (!dictionaryFile.is_open())
	{
		throw std::runtime_error("Failed to open dictionary file for writing");
	}

	for (auto const& [source, translation] : dictionary)
	{
		dictionaryFile << source << ':' << translation << '\n';
	}

	if (!dictionaryFile.flush())
	{
		throw std::runtime_error("Failed to write in the dictionary file");
	}

	dictionaryFile.close();
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

void AddTranslation(Dictionary& dictionary, const std::string& phrase, const std::string& translation)
{
	dictionary[phrase] = translation;
}

void StartTranslationConsole(const std::string& dictionaryFilename)
{
	Dictionary dictionary;
	LoadDictionary(dictionaryFilename, dictionary);

	std::string userInput;
	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, userInput);
		if (userInput == "...")
		{
			break;
		}

		auto const source = userInput;
		auto const translation = LookupTranslation(dictionary, source);
		if (translation.has_value())
		{
			std::cout << translation.value() << '\n';
		}
		else
		{
			std::cout << "> ";
			std::getline(std::cin, userInput);
			if (!userInput.empty())
			{
				AddTranslation(dictionary, source, userInput);
			}
		}
	}

	SaveDictionary(dictionaryFilename, dictionary);
}
