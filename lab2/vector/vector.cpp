#include "vector.h"

void InputVector(std::istream& stream, std::vector<double>& vector)
{
	double value;

	std::string line;
	std::getline(stream, line);
	std::stringstream input(line);

	vector.clear();
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

double CalculateMean(const std::vector<double>& vector)
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
	auto const mean = CalculateMean(positives);
	std::for_each(vector.begin(), vector.end(), [mean](double& n) { n += mean; });
}

void PrintVector(std::ostream& stream, std::vector<double>& vector)
{
	std::stringstream s;
	copy(vector.begin(), vector.end(), std::ostream_iterator<double>(s, " "));
	stream << s.str() << "\n";
}
