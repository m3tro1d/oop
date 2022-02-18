#include "vector_utils.h"

int main()
{
	try
	{
		auto vector = ReadVector(std::cin);
		AddPositivesAverageToEachElement(vector);
		PrintVector(std::cout, vector);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return EXIT_SUCCESS;
}
