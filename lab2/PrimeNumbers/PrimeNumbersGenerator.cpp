#include "PrimeNumbersGenerator.h"

using Sieve = std::vector<bool>;

Sieve GenerateSieve(int upperBound)
{
	Sieve primes(upperBound + 1, true);
	for (size_t i = 2; i * i <= upperBound; ++i)
	{
		if (primes[i])
		{
			for (size_t j = i * i; j <= upperBound; j += i)
			{
				primes[j] = false;
			}
		}
	}

	return primes;
}

std::set<int> PopulateSet(const Sieve& primes)
{
	std::set<int> result;
	for (size_t i = 2; i < primes.size(); ++i)
	{
		if (primes[i])
		{
			result.insert(static_cast<int>(i));
		}
	}

	return result;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < MIN_BOUND || upperBound > MAX_BOUND)
	{
		throw std::logic_error("Invalid upper bound value");
	}

	auto const& primes = GenerateSieve(upperBound);
	return PopulateSet(primes);
}
