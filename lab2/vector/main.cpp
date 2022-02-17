#include "vector_utils.h"

int main()
{
	std::vector<double> vector;

	InputVector(std::cin, vector);
	AddPositiveMeanToEachElement(vector);
	PrintVector(std::cout, vector);

	return EXIT_SUCCESS;
}
