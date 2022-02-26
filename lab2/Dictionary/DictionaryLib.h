#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>

using Dictionary = std::map<std::string, std::string>;

std::string ToLower(const std::string& string);

std::optional<std::string> LookupTranslation(const Dictionary& dictionary, const std::string& phrase);

void AddTranslation(Dictionary& dictionary, const std::string& phrase, const std::string& translation);
