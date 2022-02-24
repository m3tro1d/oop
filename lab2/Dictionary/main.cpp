#include "DictionaryLib.h"

int main(int argc, char** argv)
{
	auto const dictionaryFilename = GetDictionaryPath(argc, argv);

	try
	{
		StartTranslationConsole(dictionaryFilename);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
