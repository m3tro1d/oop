#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = *std::max_element(arr.begin(), arr.end(), less);

	return true;
}
