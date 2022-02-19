#define CATCH_CONFIG_MAIN
#include "../VectorProcessor.h"
#include "catch.hpp"
#include <sstream>

bool ApproximatelyEquals(const std::vector<double>& one, const std::vector<double>& two)
{
	return std::equal(
		one.begin(),
		one.end(),
		two.begin(),
		[](double a, double b) -> bool {
			return std::abs(a - b) < std::numeric_limits<double>::epsilon();
		});
}

TEST_CASE("vector is read correctly")
{
	std::stringstream input;

	SECTION("reading empty input results in an empty vector")
	{
		input.str("");
		auto vector = ReadVector(input);

		REQUIRE(vector.empty());
	}

	SECTION("numbers are read correctly")
	{
		input.str("1 2 3");
		auto vector = ReadVector(input);
		std::vector<double> result = { 1, 2, 3 };

		REQUIRE(vector == result);
	}

	SECTION("no numbers input results in an exception")
	{
		input.str("not a number");

		REQUIRE_THROWS_AS(ReadVector(input), std::invalid_argument);
	}

	SECTION("input containing several lines is read correctly")
	{
		input.str("1\n2\n3\n");
		auto vector = ReadVector(input);
		std::vector<double> result = { 1, 2, 3 };

		REQUIRE(vector == result);
	}
}

TEST_CASE("vector is processed correctly")
{
	SECTION("empty vector results in an empty vector")
	{
		std::vector<double> vector;
		AddPositivesAverageToEachElement(vector);

		REQUIRE(vector.empty());
	}

	SECTION("vector of all positive elements is processed correctly")
	{
		std::vector<double> vector = { 1, 2, 3 };
		AddPositivesAverageToEachElement(vector);
		std::vector<double> result = { 3, 4, 5 };

		REQUIRE(ApproximatelyEquals(vector, result));
	}

	SECTION("vector of all negative elements is not changed")
	{
		std::vector<double> vector{ -1, -2, -3 };
		AddPositivesAverageToEachElement(vector);
		std::vector<double> result{ -1, -2, -3 };

		REQUIRE(vector == result);
	}

	SECTION("mixed positive-negative and zeros vector is processed correctly")
	{
		std::vector<double> vector = { 1, 0, 0, -1, 2, 3, -5 };
		AddPositivesAverageToEachElement(vector);
		std::vector<double> result = { 3, 2, 2, 1, 4, 5, -3 };

		REQUIRE(ApproximatelyEquals(vector, result));
	}

	SECTION("all zeros vector results is not changed")
	{
		std::vector<double> vector(42, 0);
		AddPositivesAverageToEachElement(vector);
		std::vector<double> result(42, 0);

		REQUIRE(vector == result);
	}
}

TEST_CASE("vector is printed correctly")
{
	std::stringstream output;

	SECTION("empty vector results in an empty line")
	{
		output.clear();
		std::vector<double> vector;
		PrintVector(output, vector);
		REQUIRE(output.str() == "\n");
	}

	SECTION("usual vector results in a fixed-number output")
	{
		output.clear();
		std::vector<double> vector{ 1, 2.5431, 2.5, 3.5439 };
		PrintVector(output, vector);
		REQUIRE(output.str() == "1.000 2.543 2.500 3.544 \n");
	}
}
