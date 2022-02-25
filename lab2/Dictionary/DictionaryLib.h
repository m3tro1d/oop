#pragma once

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

const std::string DEFAULT_DICTIONARY_PATH = "dictionary.txt";

const std::string PROMPT = "> ";

using Dictionary = std::map<std::string, std::string>;

std::string tolower(const std::string& string);

std::string GetDictionaryPath(int argc, char** argv);
void ReadDictionaryFile(std::istream& dictionaryFile, Dictionary& dictionary);
void LoadDictionary(const std::string& dictionaryPath, Dictionary& dictionary);
void WriteDictionaryFile(std::ostream& dictionaryFile, const Dictionary& dictionary);
void SaveDictionary(const std::string& dictionaryFilename, const Dictionary& dictionary);

std::optional<std::string> LookupTranslation(const Dictionary& dictionary, const std::string& phrase);
void AddTranslation(Dictionary& dictionary, const std::string& phrase, const std::string& translation);

void PromptForSave(const std::string& dictionaryPath, const Dictionary& dictionary);
void StartTranslationConsole(const std::string& dictionaryFilename);
