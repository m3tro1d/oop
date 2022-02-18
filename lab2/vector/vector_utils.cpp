#include "vector_utils.h"

constexpr int PRINT_PRECISION = 3;

std::vector<double> InputVector(std::istream& input)
{
	std::vector<double> result;
	double value;
	while (input >> value)
	{
		result.push_back(value);
	}

	if (input.bad())
	{
		throw std::invalid_argument("Invalid input");
	}

	return result;
}

void PrintVector(std::ostream& output, const std::vector<double>& vector)
{
	output << std::fixed << std::setprecision(PRINT_PRECISION);
	std::copy(vector.begin(), vector.end(), std::ostream_iterator<double>(output, " "));
	output << '\n';
}
