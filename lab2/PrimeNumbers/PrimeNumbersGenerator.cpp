#include "PrimeNumbersGenerator.h"

using Sieve = std::vector<bool>;

std::set<int> PopulateSet(int upperBound)
{
	Sieve primes(upperBound + 1, true);
	std::set<int> result;

	result.insert(2);
	const double sizeSquareRoot = std::sqrt(primes.size());

	for (size_t i = 3; i < primes.size(); i += 2)
	{
		if (primes[i])
		{
			result.insert(static_cast<int>(i));

			if (i < sizeSquareRoot)
			{
				for (size_t j = i * i; j < primes.size(); j += i)
				{
					primes[j] = false;
				}
			}
		}
	}

	return result;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < MIN_BOUND || upperBound > MAX_BOUND)
	{
		throw std::out_of_range("Invalid upper bound value");
	}

	return PopulateSet(upperBound);
}
