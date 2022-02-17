#define CATCH_CONFIG_MAIN
#include "../vector_utils.h"
#include "catch.hpp"
#include <sstream>

TEST_CASE("Empty string input produces empty vector", "[input]")
{
	std::stringstream input("");
	std::vector<double> vector;

	InputVector(input, vector);
	REQUIRE(vector.empty());
}

TEST_CASE("Vector's contents contain numbers from input", "[input]")
{
	std::stringstream input("1 2 -3 2.4");
	std::vector<double> vector;

	InputVector(input, vector);
	REQUIRE(vector == std::vector<double>{ 1, 2, -3, 2.4 });
}

TEST_CASE("Empty vector is processed correctly", "[processing]")
{
	std::vector<double> vector;

	AddPositiveMeanToEachElement(vector);
	REQUIRE(vector.empty());
}

TEST_CASE("Vector containing arbitrary numbers is processed correctly", "[processing]")
{
	std::vector<double> vector{ 1, 2, -4, 3, -5, 0 };

	AddPositiveMeanToEachElement(vector);
	REQUIRE(vector == std::vector<double>{ 3, 4, -2, 5, -3, 2 });
}

TEST_CASE("Vector with only one positive is processed correctly", "[processing]")
{
	std::vector<double> vector{ -1, 2, -3, -4 };

	AddPositiveMeanToEachElement(vector);
	REQUIRE(vector == std::vector<double>{ 1, 4, -1, -2 });
}

TEST_CASE("All positive numbers are processed correctly", "[processing]")
{
	std::vector<double> vector{ 1, 2, 3 };

	AddPositiveMeanToEachElement(vector);
	REQUIRE(vector == std::vector<double>{ 3, 4, 5 });
}

TEST_CASE("All negative numbers are processed correctly, resulting in the same vector", "[processing]")
{
	std::vector<double> vector{ -1, -2, -3 };

	AddPositiveMeanToEachElement(vector);
	REQUIRE(vector == std::vector<double>{ -1, -2, -3 });
}

TEST_CASE("All zeros are processed correctly, resulting in the same vector", "[processing]")
{
	std::vector<double> vector{ 0, 0, 0, 0, 0 };

	AddPositiveMeanToEachElement(vector);
	REQUIRE(vector == std::vector<double>{ 0, 0, 0, 0, 0 });
}

TEST_CASE("Empty vector produces empty output with newline at the end", "[output]")
{
	std::stringstream output;
	std::vector<double> vector;

	PrintVector(output, vector);
	REQUIRE(output.str() == "\n");
}

TEST_CASE("Output contains vector's contents", "[output]")
{
	std::stringstream output;
	std::vector<double> vector{ 1, 2, -3, 2.4 };

	PrintVector(output, vector);
	REQUIRE(output.str() == "1.000 2.000 -3.000 2.400 \n");
}
