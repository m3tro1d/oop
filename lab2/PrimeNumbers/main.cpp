#include "PrimeNumbersGenerator.h"
#include <iostream>
#include <iterator>
#include <optional>

std::optional<int> GetUpperBound(int argc, char** argv);
void PrintPrimes(std::ostream& output, const std::set<int>& primes);

int main(int argc, char** argv)
{
	auto const upperBound = GetUpperBound(argc, argv);
	if (!upperBound.has_value())
	{
		return EXIT_FAILURE;
	}

	try
	{
		auto const primes = GeneratePrimeNumbersSet(upperBound.value());
		PrintPrimes(std::cout, primes);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return EXIT_SUCCESS;
}

std::optional<int> GetUpperBound(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Invalid argument count\n"
				  << "Usage: PrimeNumbers.exe <upper bound>\n";
		return std::nullopt;
	}

	int upperBound;
	try
	{
		upperBound = std::stoi(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Invalid upper bound - should be a number\n";
		return std::nullopt;
	}

	return upperBound;
}

void PrintPrimes(std::ostream& output, const std::set<int>& primes)
{
	std::copy(
		primes.begin(),
		primes.end(),
		std::ostream_iterator<int>(std::cout, " "));
	std::cout << '\n';
}
