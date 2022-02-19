#include "HTMLProcessor.h"

int main()
{
	try
	{
		HtmlDecode(std::cin, std::cout);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return EXIT_SUCCESS;
}
