#include "ExpandTemplateLib.h"

int main(int argc, char** argv)
{
	auto const args = ParseArgs(argc, argv);
	if (!args.has_value())
	{
		std::cerr << "Invalid argument count\n"
				  << "Usage: ExpandTemplate.exe <input filename> <output filename> "
				  << "[<param> <value> [<param> <value> ...]]\n";
		return EXIT_FAILURE;
	}

	try
	{
		std::ifstream input;
		InitializeInputFile(input, args->inputFilename);

		std::ofstream output;
		InitializeOutputFile(output, args->outputFilename);

		ExpandTemplates(input, output, args->params);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
