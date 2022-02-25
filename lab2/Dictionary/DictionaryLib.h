#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <optional>
#include <sstream>
#include <string>

const std::string DEFAULT_DICTIONARY_PATH = "dictionary.txt";

const std::string PROMPT = "> ";

using Dictionary = std::map<std::string, std::string>;

std::string tolower(const std::string& string);

std::string GetDictionaryPath(int argc, char** argv);
void LoadDictionary(const std::string& dictionaryPath, Dictionary& dictionary);
void SaveDictionary(const std::string& dictionaryFilename, const Dictionary& dictionary);

std::optional<std::string> LookupTranslation(const Dictionary& dictionary, const std::string& phrase);
void AddTranslation(Dictionary& dictionary, const std::string& phrase, const std::string& translation);

void PromptForSave(const std::string& dictionaryPath, const Dictionary& dictionary);

void StartTranslationConsole(const std::string& dictionaryFilename);
