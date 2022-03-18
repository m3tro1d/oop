#include "ShapeProcessor.h"

int main()
{
	try
	{
		ShapeProcessor processor(std::cin, std::cout);
		processor.ProcessShapes();
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
