#include <fstream>
#include <iostream>
#include <string>
#include <optional>

struct Args
{
	std::string inputFilename;
	std::string outputFilename;
	std::string searchPattern;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char** argv);
void CopyWithReplace(std::istream& input, std::ostream& output, const std::string& searchPattern, const std::string& replaceString);

int main(int argc, char** argv)
{
	auto const args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cerr << "Invalid argument count\n"
				  << "Usage: replace.exe <input file> <output file> <search pattern> <replace string>\n";
		return EXIT_FAILURE;
	}

	std::ifstream inputFile;
	inputFile.open(args->inputFilename);
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open input file '" << args->inputFilename << "' for reading\n";
		return EXIT_FAILURE;
	}

	std::ofstream outputFile;
	outputFile.open(args->outputFilename);
	if (!outputFile.is_open())
	{
		std::cerr << "Failed to open output file '" << args->outputFilename << "' for writing\n";
		return EXIT_FAILURE;
	}

	CopyWithReplace(inputFile, outputFile, args->searchPattern, args->replaceString);

	if (inputFile.bad())
	{
		std::cerr << "Failed to read from input file\n";
		return EXIT_FAILURE;
	}

	if (!outputFile.flush())
	{
		std::cerr << "Failed to write to output file\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc != 5)
	{
		return std::nullopt;
	}

	Args args;
	args.inputFilename = argv[1];
	args.outputFilename = argv[2];
	args.searchPattern = argv[3];
	args.replaceString = argv[4];

	return args;
}

std::string ReplaceString(const std::string& string, const std::string& searchPattern, const std::string& replaceString)
{
	size_t pos = 0;
	std::string result;
	while (pos < string.length())
	{
		size_t foundPos = string.find(searchPattern, pos);
		result.append(string, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			result.append(replaceString);
			pos = foundPos + searchPattern.length();
		}
		else
		{
			break;
		}
	}

	return result;
}

void CopyWithReplace(std::istream& input, std::ostream& output, const std::string& searchPattern, const std::string& replaceString)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchPattern, replaceString) << "\n";
	}
}
