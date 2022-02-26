#include "ExpandTemplateLib.h"

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc < 5 || (argc - 3) % 2)
	{
		return std::nullopt;
	}

	Args args;
	args.inputFilename = argv[1];
	args.outputFilename = argv[2];
	for (size_t i = 3; i < argc - 1; ++i)
	{
		args.params[argv[i]] = argv[i + 1];
	}

	return args;
}

void InitializeInputFile(std::ifstream& input, const std::string& filename)
{
	input.open(filename);
	if (!input.is_open())
	{
		throw std::runtime_error("failed to open input file for reading");
	}
}

void InitializeOutputFile(std::ofstream& output, const std::string& filename)
{
	output.open(filename);
	if (!output.is_open())
	{
		throw std::runtime_error("failed to open output file for writing");
	}
}

std::string ExpandTemplate(const std::string& tpl, const TemplateParams& params)
{
	// TODO
	return tpl;
}

void ExpandTemplates(std::istream& input, std::ostream& output, const TemplateParams& params)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << ExpandTemplate(line, params) << '\n';
	}

	if (!output.flush())
	{
		throw std::runtime_error("failed to write to output file");
	}
}
