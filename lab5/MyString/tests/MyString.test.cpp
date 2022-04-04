#define CATCH_CONFIG_MAIN
#include "../CMyString.h"
#include "catch.hpp"

TEST_CASE("string creation")
{
	SECTION("empty string")
	{
		CMyString s;

		REQUIRE(s.GetStringData()[0] == '\0');
		REQUIRE(s.GetLength() == 0);
	}

	SECTION("using C string")
	{
		auto const cString = "Hello, wonderful World!";
		CMyString s(cString);

		REQUIRE(std::strcmp(s.GetStringData(), cString) == 0);
		REQUIRE(s.GetLength() == std::strlen(cString));
	}

	SECTION("using char pointer and length")
	{
		auto const cString = "Hello, wonderful World!";
		size_t const length = 5;
		CMyString s(cString, length);
		auto const stringData = s.GetStringData();

		REQUIRE(std::strcmp(stringData, "Hello") == 0);
		REQUIRE(s.GetLength() == length);
	}

	SECTION("using STL string")
	{
		std::string const stlString = "Hello, wonderful World of C++ standard library!";
		CMyString s(stlString);

		REQUIRE(s.GetStringData() == stlString);
		REQUIRE(s.GetLength() == stlString.length());
	}
}

TEST_CASE("string creation from other strings")
{
	SECTION("copying")
	{
		SECTION("copy contains the same string with the same length")
		{
			CMyString s = "Hello, wonderful World!";
			CMyString copy(s);

			REQUIRE(std::strcmp(s.GetStringData(), copy.GetStringData()) == 0);
			REQUIRE(s.GetLength() == copy.GetLength());
		}

		SECTION("modifying the copy does not affect the original string")
		{
			char const* initialString = "Hello, wonderful World!";
			CMyString s = initialString;
			CMyString copy(s);
			char* firstCharPtr = const_cast<char*>(copy.GetStringData());
			*firstCharPtr = 'B';

			REQUIRE(std::strcmp(s.GetStringData(), initialString) == 0);
			REQUIRE(std::strcmp(copy.GetStringData(), initialString) != 0);
		}
	}

	SECTION("moving")
	{
		SECTION("moved string contains the same string with the same length")
		{
			char const* initialString = "Hello, wonderful World!";
			size_t const initialLength = std::strlen(initialString);
			CMyString s = initialString;
			CMyString moved(std::move(s));

			REQUIRE(std::strcmp(initialString, moved.GetStringData()) == 0);
			REQUIRE(initialLength == moved.GetLength());
		}

		SECTION("initial string is zeroed after moving")
		{
			CMyString s = "Hello, wonderful World!";
			CMyString moved(std::move(s));

			REQUIRE(s.GetStringData() == nullptr);
			REQUIRE(s.GetLength() == 0);
		}
	}
}

TEST_CASE("string assignment")
{
	SECTION("copy assignment")
	{
		// TODO
	}

	SECTION("move assignment")
	{
		// TODO
	}
}

TEST_CASE("string slicing")
{
	// TODO
	REQUIRE(true);
}

TEST_CASE("string clearing")
{
	// TODO
	REQUIRE(true);
}

TEST_CASE("string concatenation")
{
	SECTION("concatenation-assignment")
	{
		// TODO
	}

	SECTION("plain concatenation")
	{
		// TODO
	}
}

TEST_CASE("string comparison")
{
	SECTION("equality")
	{
		// TODO
	}

	SECTION("inequality")
	{
		// TODO
	}
}

TEST_CASE("lexicographical comparison")
{
	SECTION("strict: <, >")
	{
		// TODO
	}

	SECTION("not strict: <=, >=")
	{
		// TODO
	}
}

TEST_CASE("string input-output using streams")
{
	SECTION("writing")
	{
		// TODO
	}

	SECTION("reading")
	{
		// TODO
	}
}
