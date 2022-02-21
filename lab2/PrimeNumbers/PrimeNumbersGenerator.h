#pragma once

#include <set>
#include <stdexcept>
#include <vector>

constexpr int MIN_BOUND = 2;
constexpr int MAX_BOUND = 100000000;

std::set<int> GeneratePrimeNumbersSet(int upperBound);
