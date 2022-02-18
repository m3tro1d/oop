#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

std::vector<double> ReadVector(std::istream& input);

void MultiplyEachByMaxAndDivideByMin(std::vector<double>& vector);

void PrintVector(std::ostream& output, const std::vector<double>& vector);
