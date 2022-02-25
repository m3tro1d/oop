#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../PrimeNumbersGenerator.h"
#include "catch.hpp"

TEST_CASE("borderline cases are processed correctly")
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

	SECTION("generated set includes the upper bound if it is prime")
	{
		auto const primes1 = GeneratePrimeNumbersSet(5);
		auto const primes2 = GeneratePrimeNumbersSet(6);
		std::set<int> result = { 2, 3, 5 };

		REQUIRE(primes1 == result);
		REQUIRE(primes2 == result);
	}
}

TEST_CASE("usual cases are working correctly")
{
	auto const primes1000 = GeneratePrimeNumbersSet(1000);
	REQUIRE(primes1000.size() == 168);

	auto const primes1009 = GeneratePrimeNumbersSet(1009);
	REQUIRE(primes1009.size() == 169);
}

TEST_CASE("heavy case is working correctly")
{
	auto const primes = GeneratePrimeNumbersSet(100000000);
	REQUIRE(primes.size() == 5761455);
}
