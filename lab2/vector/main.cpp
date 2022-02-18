#include "vector_utils.h"

int main()
{
	try
	{
		auto vector = InputVector(std::cin);
		PrintVector(std::cout, vector);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	return EXIT_SUCCESS;
}
