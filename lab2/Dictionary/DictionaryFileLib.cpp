#include "DictionaryFileLib.h"

std::string GetDictionaryPath(int argc, char** argv)
{
	if (argc != 2)
	{
		return DEFAULT_DICTIONARY_PATH;
	}

	return argv[1];
}

void ReadDictionaryFile(std::istream& dictionaryFile, Dictionary& dictionary)
{
	std::string source;
	std::string translations;
	while (std::getline(dictionaryFile, source))
	{
		if (!std::getline(dictionaryFile, translations))
		{
			return;
		}

		if (source.empty() || translations.empty())
		{
			throw std::invalid_argument("Invalid dictionary file format");
		}

		AddTranslations(dictionary, source, translations);
	}

	if (dictionaryFile.eof() && !source.empty())
	{
		throw std::invalid_argument("Invalid dictionary file format");
	}
}

void LoadDictionary(const std::string& dictionaryPath, Dictionary& dictionary)
{
	std::ifstream dictionaryFile(dictionaryPath);
	if (!dictionaryFile.is_open())
	{
		return;
	}

	ReadDictionaryFile(dictionaryFile, dictionary);

	if (dictionaryFile.bad())
	{
		throw std::runtime_error("failed to read from input file");
	}

	dictionaryFile.close();
}

void WriteDictionaryFile(std::ostream& dictionaryFile, const Dictionary& dictionary)
{
	for (auto const& [source, translation] : dictionary)
	{
		dictionaryFile << source << '\n'
					   << SerializeTranslationsAsString(translation) << '\n';
	}
}

void SaveDictionary(const std::string& dictionaryPath, const Dictionary& dictionary)
{
	std::ofstream dictionaryFile(dictionaryPath);
	if (!dictionaryFile.is_open())
	{
		throw std::runtime_error("Failed to open dictionary file for writing");
	}

	WriteDictionaryFile(dictionaryFile, dictionary);

	if (!dictionaryFile.flush())
	{
		throw std::runtime_error("Failed to write in the dictionary file");
	}

	dictionaryFile.close();
}
