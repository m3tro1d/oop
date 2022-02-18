#include "vector_utils.h"

constexpr int PRINT_PRECISION = 3;

std::vector<double> ReadVector(std::istream& input)
{
	std::vector<double> result;
	double value;
	while (input >> value)
	{
		result.push_back(value);
	}

	if (!input.eof() || input.bad())
	{
		throw std::invalid_argument("Invalid input");
	}

	return result;
}

bool IsZero(double value)
{
	return std::abs(value) < std::numeric_limits<double>::epsilon();
}

void MultiplyEachByMaxAndDivideByMin(std::vector<double>& vector)
{
	auto const max = std::max_element(vector.begin(), vector.end());
	auto const min = std::min_element(vector.begin(), vector.end());

	if (IsZero(*min))
	{
		throw std::logic_error("Minimum element is 0, can not divide");
	}

	std::for_each(
		vector.begin(),
		vector.end(),
		[max, min](double& value) {
			value *= *max / *min;
		});
}

void PrintVector(std::ostream& output, const std::vector<double>& vector)
{
	output << std::fixed << std::setprecision(PRINT_PRECISION);
	std::copy(vector.begin(), vector.end(), std::ostream_iterator<double>(output, " "));
	output << '\n';
}
