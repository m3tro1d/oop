#pragma once

#include "DictionaryFileLib.h"
#include "DictionaryLib.h"
#include <iomanip>

const std::string PROMPT = "> ";
const std::string EXIT_INPUT = "...";

bool PromptForNewWord(
	std::istream& input,
	std::ostream& output,
	Dictionary& dictionary,
	const std::string& source);

void PromptForSave(
	std::istream& input,
	std::ostream& output,
	const std::string& dictionaryPath,
	const Dictionary& dictionary);

void StartTranslationConsole(std::istream& input, std::ostream& output, const std::string& dictionaryFilename);
