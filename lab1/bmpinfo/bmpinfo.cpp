#include <fstream>
#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> GetInputFilename(int argc, char** argv);

int main(int argc, char** argv)
{
	auto const inputFilename = GetInputFilename(argc, argv);
	if (!inputFilename)
	{
		std::cerr << "Invalid argument count\n"
				  << "Usage: bmpinfo.exe <input file name>\n";
		return EXIT_FAILURE;
	}

	std::ifstream inputFile(inputFilename.value());
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open input file '" << inputFilename.value() << "' for reading\n";
		return EXIT_FAILURE;
	}

	// TODO: 1. Parse file
	//       2. Parse the header and print error if it's not a BMP
	//       3. Print the headers

	return EXIT_SUCCESS;
}

std::optional<std::string> GetInputFilename(int argc, char** argv)
{
	if (argc != 2)
	{
		return std::nullopt;
	}

	return argv[1];
}
