#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFilename;
	std::string outputFilename;
	std::string searchPattern;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char** argv);
bool InitializeFiles(std::ifstream& inputFile, std::ofstream& outputFile, const Args& args);
void CopyWithReplace(std::istream& input, std::ostream& output, const std::string& searchPattern, const std::string& replaceString);
bool CleanUpFiles(std::ifstream& inputFile, std::ofstream& outputFile);

int main(int argc, char** argv)
{
	auto const args = ParseArgs(argc, argv);
	if (!args.has_value())
	{
		std::cerr << "Invalid argument count\n"
				  << "Usage: replace.exe <input file> <output file> <search pattern> <replace string>\n";
		return EXIT_FAILURE;
	}

	std::ifstream inputFile;
	std::ofstream outputFile;
	if (!InitializeFiles(inputFile, outputFile, args.value()))
	{
		return EXIT_FAILURE;
	}

	CopyWithReplace(inputFile, outputFile, args->searchPattern, args->replaceString);
	CleanUpFiles(inputFile, outputFile);

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

bool InitializeFiles(std::ifstream& inputFile, std::ofstream& outputFile, const Args& args)
{
	inputFile.open(args.inputFilename);
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open input file '" << args.inputFilename << "' for reading\n";
		return false;
	}

	outputFile.open(args.outputFilename);
	if (!outputFile.is_open())
	{
		std::cerr << "Failed to open output file '" << args.outputFilename << "' for writing\n";
		return false;
	}

	return true;
}

std::string ReplaceString(const std::string& string, const std::string& searchPattern, const std::string& replaceString)
{
	size_t searchPosition = 0;
	std::string result;
	while (searchPosition < string.length())
	{
		size_t replacePosition = string.find(searchPattern, searchPosition);
		result.append(string, searchPosition, replacePosition - searchPosition);

		if (replacePosition == std::string::npos)
		{
			break;
		}

		result.append(replaceString);
		searchPosition = replacePosition + searchPattern.length();
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

bool CleanUpFiles(std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (inputFile.bad())
	{
		std::cerr << "Failed to read from input file\n";
		return false;
	}

	if (!outputFile.flush())
	{
		std::cerr << "Failed to write to output file\n";
		return false;
	}

	return true;
}
