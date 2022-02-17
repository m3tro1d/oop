#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

constexpr int PRINT_PRECISION = 3;

void InputVector(std::istream& input, std::vector<double>& vector);

void AddPositiveMeanToEachElement(std::vector<double>& vector);

void PrintVector(std::ostream& output, std::vector<double>& vector);
