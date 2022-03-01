#pragma once

#include <set>
#include <sstream>
#include <string>

std::string ToLower(const std::string& string);

void Trim(std::string& string);

std::set<std::string> StringToSet(const std::string& string, char delimiter);

std::string SetToString(const std::set<std::string>& set, const std::string& delimiter);
