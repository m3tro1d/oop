#pragma once

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <optional>
#include <vector>

std::vector<double> ReadVector(std::istream& input);

void AddPositivesAverageToEachElement(std::vector<double>& vector);

void SortVector(std::vector<double>& vector);

void PrintVector(std::ostream& output, const std::vector<double>& vector);
