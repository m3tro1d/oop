#include "DictionaryConsoleLib.h"

int main(int argc, char** argv)
{
	auto const dictionaryFilename = GetDictionaryPath(argc, argv);

	try
	{
		StartTranslationConsole(std::cin, std::cout, dictionaryFilename);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
