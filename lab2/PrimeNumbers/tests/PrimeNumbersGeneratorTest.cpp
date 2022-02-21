#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../PrimeNumbersGenerator.h"
#include "catch.hpp"

TEST_CASE("prime generation is working correctly")
{
	SECTION("wrong upper bound results in an exception")
	{
		REQUIRE_THROWS_AS(GeneratePrimeNumbersSet(MIN_BOUND - 1), std::logic_error);
		REQUIRE_THROWS_AS(GeneratePrimeNumbersSet(MAX_BOUND + 1), std::logic_error);
	}

	SECTION("minimal upper bound results in the only number")
	{
		auto const primes = GeneratePrimeNumbersSet(2);
		std::set<int> result = { 2 };

		REQUIRE(primes == result);
	}

	SECTION("prime numbers are generated correctly")
	{
		auto const primes = GeneratePrimeNumbersSet(10);
		std::set<int> result = { 2, 3, 5, 7 };

		REQUIRE(primes == result);
	}

	SECTION("generated set includes the upper bound if it is prime")
	{
		auto const primes = GeneratePrimeNumbersSet(5);
		std::set<int> result = { 2, 3, 5 };

		REQUIRE(primes.find(5) != primes.end());
	}
}
