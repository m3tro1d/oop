#include "DictionaryLib.h"

std::string tolower(const std::string& string)
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
	std::string line;
	while (std::getline(dictionaryFile, line))
	{
		if (line.empty())
		{
			continue;
		}

		std::string source;
		std::string translation;

		std::stringstream translationUnit(line);
		std::getline(translationUnit, source, ':');
		std::getline(translationUnit, translation);

		if (source.empty() || translation.empty())
		{
			throw std::invalid_argument("Invalid dictionary file format");
		}

		dictionary[source] = translation;
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
		dictionaryFile << source << ':' << translation << '\n';
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

bool PromptForNewWord(
	std::istream& input,
	std::ostream& output,
	Dictionary& dictionary,
	const std::string& source)
{
	std::string userInput;
	bool saved = false;

	output << "Unknown word '" << source << "'. Enter translation or empty string to abort.\n"
		   << PROMPT;
	std::getline(input, userInput);
	if (!userInput.empty())
	{
		AddTranslation(dictionary, tolower(source), userInput);
		saved = true;
		output << "Word '" << source << "' saved in the dictionary as '" << userInput << "'.\n";
	}
	else
	{
		output << "Word '" << source << "' ignored. Good riddance.\n";
	}

	return saved;
}

void PromptForSave(
	std::istream& input,
	std::ostream& output,
	const std::string& dictionaryPath,
	const Dictionary& dictionary)
{
	output << "Dictionary has been changed. Enter Y or y to save changes.\n"
		   << PROMPT;

	char answer;
	input >> answer;
	if (std::tolower(answer) == 'y')
	{
		SaveDictionary(dictionaryPath, dictionary);
		output << "Changes saved successfully. Farewell!\n";
	}
	else
	{
		output << "Changes discarded. Have a nice day!\n";
	}
}

void StartTranslationConsole(std::istream& input, std::ostream& output, const std::string& dictionaryPath)
{
	Dictionary dictionary;
	LoadDictionary(dictionaryPath, dictionary);

	std::string userInput;
	bool dictionaryChanged = false;
	while (true)
	{
		output << PROMPT;
		std::getline(input, userInput);
		if (userInput == EXIT_INPUT)
		{
			break;
		}

		auto const translation = LookupTranslation(dictionary, tolower(userInput));
		if (translation.has_value())
		{
			output << translation.value() << '\n';
		}
		else
		{
			dictionaryChanged = PromptForNewWord(input, output, dictionary, userInput);
		}
	}

	if (dictionaryChanged)
	{
		PromptForSave(input, output, dictionaryPath, dictionary);
	}
	else
	{
		output << "No changes in the dictionary. Come back soon!\n";
	}
}
