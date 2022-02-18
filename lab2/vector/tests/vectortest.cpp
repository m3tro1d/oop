#define CATCH_CONFIG_MAIN
#include "../vector_utils.h"
#include "catch.hpp"
#include <sstream>

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
		REQUIRE(vector == std::vector<double>{ 1, 2, 3 });
	}

	SECTION("no numbers input results in an exception")
	{
		input.str("not a number");
		REQUIRE_THROWS_AS(ReadVector(input), std::invalid_argument);
	}

	SECTION("several lines of input are read correctly")
	{
		input.str("1\n2\n3\n");
		auto vector = ReadVector(input);
		REQUIRE(vector == std::vector<double>{ 1, 2, 3 });
	}
}

TEST_CASE("vector is processed correctly")
{
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
