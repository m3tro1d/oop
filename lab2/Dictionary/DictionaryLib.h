#pragma once

#include "StringLib.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

constexpr char DELIMITER = ',';

using Translations = std::set<std::string>;
using Dictionary = std::map<std::string, Translations>;

std::optional<Translations> LookupTranslation(const Dictionary& dictionary, const std::string& phrase);

void AddDirectTranslations(Dictionary& dictionary, const std::string& phrase, const Translations& translations);

void AddReverseTranslations(Dictionary& dictionary, const Translations& translations, const std::string& phrase);

void AddTranslations(Dictionary& dictionary, const std::string& phrase, const Translations& translations);

void AddTranslations(Dictionary& dictionary, const std::string& phrase, const std::string& translationsString);
