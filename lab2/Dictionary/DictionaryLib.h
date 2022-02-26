#pragma once

#include <iostream>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>

const std::string DEFAULT_DICTIONARY_PATH = "dictionary.txt";

const std::string PROMPT = "> ";
const std::string EXIT_INPUT = "...";

using Dictionary = std::map<std::string, std::string>;

std::optional<std::string> LookupTranslation(const Dictionary& dictionary, const std::string& phrase);
void AddTranslation(Dictionary& dictionary, const std::string& phrase, const std::string& translation);
