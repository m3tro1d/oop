#pragma once

#include "DictionaryLib.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

const std::string DEFAULT_DICTIONARY_PATH = "dictionary.txt";

std::string tolower(const std::string& string);

std::string GetDictionaryPath(int argc, char** argv);
void ReadDictionaryFile(std::istream& dictionaryFile, Dictionary& dictionary);
void LoadDictionary(const std::string& dictionaryPath, Dictionary& dictionary);
void WriteDictionaryFile(std::ostream& dictionaryFile, const Dictionary& dictionary);
void SaveDictionary(const std::string& dictionaryFilename, const Dictionary& dictionary);
