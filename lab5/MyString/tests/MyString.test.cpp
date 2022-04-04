#define CATCH_CONFIG_MAIN
#include "../CMyString.h"
#include "catch.hpp"

TEST_CASE("string creation")
{
	SECTION("empty string")
	{
		CMyString s;
		auto const stringData = s.GetStringData();

		REQUIRE(s.GetLength() == 0);
		REQUIRE(stringData[0] == '\0');
	}

	SECTION("using C string")
	{
		auto const cString = "Hello, wonderful World!";
		CMyString s(cString);
		auto const stringData = s.GetStringData();

		REQUIRE(s.GetLength() == std::strlen(cString));
		REQUIRE(std::strcmp(stringData, cString) == 0);
	}

	SECTION("using char pointer and length")
	{
		auto const cString = "Hello, wonderful World!";
		int const length = 5;
		CMyString s(cString, length);
		auto const stringData = s.GetStringData();

		REQUIRE(s.GetLength() == length);
		REQUIRE(std::strcmp(stringData, "Hello") == 0);
	}

	SECTION("using STL string")
	{
		std::string const stlString = "Hello, wonderful World of C++ standard library!";
		CMyString s(stlString);
		auto const stringData = s.GetStringData();

		REQUIRE(s.GetLength() == stlString.length());
		REQUIRE(stringData == stlString);
	}
}

TEST_CASE("string copying")
{
	// TODO
	REQUIRE(true);
}

TEST_CASE("string moving")
{
	// TODO
	REQUIRE(true);
}
