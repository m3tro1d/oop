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

std::optional<double> FindPositivesAverage(const std::vector<double>& vector)
{
	double sum = 0;
	int count = 0;
	std::for_each(
		vector.begin(),
		vector.end(),
		[&](double element) {
			if (element > 0)
			{
				sum += element;
				++count;
			}
		});

	if (count == 0)
	{
		return std::nullopt;
	}

	return sum / static_cast<double>(count);
}

void AddPositivesAverageToEachElement(std::vector<double>& vector)
{
	if (vector.empty())
	{
		return;
	}

	auto const positivesAverage = FindPositivesAverage(vector);
	if (!positivesAverage.has_value())
	{
		throw std::logic_error("Can't find average if there's no positive elements");
	}

	std::for_each(
		vector.begin(),
		vector.end(),
		[positivesAverage](double& element) {
			element += positivesAverage.value();
		});
}

void PrintVector(std::ostream& output, const std::vector<double>& vector)
{
	output << std::fixed << std::setprecision(PRINT_PRECISION);
	std::copy(vector.begin(), vector.end(), std::ostream_iterator<double>(output, " "));
	output << '\n';
}
