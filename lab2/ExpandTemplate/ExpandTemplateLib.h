#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>

struct Args
{
	std::string inputFilename;
	std::string outputFilename;
	std::map<std::string, std::string> params;
};

using TemplateParams = std::map<std::string, std::string>;

std::optional<Args> ParseArgs(int argc, char** argv);

void InitializeInputFile(std::ifstream& input, const std::string& filename);

void InitializeOutputFile(std::ofstream& output, const std::string& filename);

std::string ExpandTemplate(const std::string& tpl, const TemplateParams& params);

void ExpandTemplates(std::istream& input, std::ostream& output, const TemplateParams& params);
