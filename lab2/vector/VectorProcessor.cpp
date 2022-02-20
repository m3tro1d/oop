#include "VectorProcessor.h"

constexpr int PRINT_PRECISION = 3;

std::vector<double> ReadVector(std::istream& input)
{
	std::vector<double> result;
	std::copy(
		std::istream_iterator<double>(input),
		std::istream_iterator<double>(),
		std::back_inserter(result));

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
		return;
	}

	std::for_each(
		vector.begin(),
		vector.end(),
		[&](double& element) {
			element += positivesAverage.value();
		});
}

void SortVector(std::vector<double>& vector)
{
	std::sort(vector.begin(), vector.end());
}

void PrintVector(std::ostream& output, const std::vector<double>& vector)
{
	output << std::fixed << std::setprecision(PRINT_PRECISION);
	std::copy(vector.begin(), vector.end(), std::ostream_iterator<double>(output, " "));
	output << '\n';
}
