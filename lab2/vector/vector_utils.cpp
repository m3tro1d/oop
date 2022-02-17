#include "vector_utils.h"

void InputVector(std::istream& input, std::vector<double>& vector)
{
	vector.clear();

	double value;
	while (input >> value)
	{
		vector.push_back(value);
	}
}

std::vector<double> FindPositives(const std::vector<double>& vector)
{
	std::vector<double> result;
	std::copy_if(vector.begin(), vector.end(), std::back_inserter(result), [](double n) { return n > 0; });

	return result;
}

double CalculateAverage(const std::vector<double>& vector)
{
	if (vector.empty())
	{
		return 0;
	}

	auto const count = static_cast<double>(vector.size());
	return std::accumulate(vector.begin(), vector.end(), 0.0) / count;
}

void AddPositiveMeanToEachElement(std::vector<double>& vector)
{
	auto const positives = FindPositives(vector);
	auto const average = CalculateAverage(positives);
	std::for_each(vector.begin(), vector.end(), [average](double& n) { n += average; });
}

void PrintVector(std::ostream& output, std::vector<double>& vector)
{
	output << std::fixed << std::setprecision(PRINT_PRECISION);
	std::copy(vector.begin(), vector.end(), std::ostream_iterator<double>(output, " "));
	output << '\n';
}
