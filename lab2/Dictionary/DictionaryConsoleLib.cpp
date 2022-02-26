#include "DictionaryConsoleLib.h"

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
		AddTranslation(dictionary, source, userInput);
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

		auto const translation = LookupTranslation(dictionary, userInput);
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
