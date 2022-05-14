#pragma once

#include <vector>

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = arr.front();
	for (auto const& element : arr)
	{
		if (less(maxValue, element))
		{
			maxValue = element;
		}
	}

	return true;
}
