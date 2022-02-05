#include <vector.h>

constexpr int SUCCESS = 0;

int main()
{
	std::vector<double> vector;

	InputVector(std::cin, vector);
	AddPositiveMeanToEachElement(vector);
	PrintVector(std::cout, vector);

	return SUCCESS;
}
