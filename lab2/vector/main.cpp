#include "VectorProcessor.h"

int main()
{
	try
	{
		auto vector = ReadVector(std::cin);
		AddPositivesAverageToEachElement(vector);
		SortVector(vector);
		PrintVector(std::cout, vector);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return EXIT_SUCCESS;
}
