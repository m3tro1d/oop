#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

std::string HtmlDecode(const std::string& html);

void HtmlDecode(std::istream& input, std::ostream& output);
