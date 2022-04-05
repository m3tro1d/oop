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
	CMyString s = "Hello, wonderful World!";

	SECTION("slicing with fixed length returns a substring of specified length")
	{
		size_t const start = 0;
		size_t const length = 5;

		auto const subString = s.SubString(start, length);

		REQUIRE(std::strcmp(subString.GetStringData(), "Hello") == 0);
	}

	SECTION("slicing without explicit length returns all original string to the end")
	{
		size_t const start = 7;

		auto const subString = s.SubString(start);

		REQUIRE(std::strcmp(subString.GetStringData(), "wonderful World!") == 0);
	}

	SECTION("if length is out of range, returns all original string to the end")
	{
		size_t const start = 7;
		size_t const length = 420;

		auto const subString = s.SubString(start, length);

		REQUIRE(std::strcmp(subString.GetStringData(), "wonderful World!") == 0);
	}

	SECTION("out of range start index results in an error")
	{
		size_t const start = 420;

		REQUIRE_THROWS_AS(s.SubString(start), std::out_of_range);
	}
}

TEST_CASE("string clearing")
{
	CMyString s = "Hello, wonderful World!";
	s.Clear();

	REQUIRE(std::strcmp(s.GetStringData(), "") == 0);
	REQUIRE(s.GetLength() == 0);
}

TEST_CASE("subscript access")
{
	SECTION("modifying the character changes the string")
	{
		CMyString s = "Hello, wonderful World!";
		s[0] = 'W';

		REQUIRE(std::strcmp(s.GetStringData(), "Wello, wonderful World!") == 0);
	}

	SECTION("getting constant character at specified index works correctly")
	{
		CMyString const s = "Hello, wonderful World!";

		REQUIRE(s[5] == ',');
	}

	SECTION("trying to access index out of range results in an error")
	{
		CMyString s = "Hello, wonderful World!";
		CMyString const sConst = "Hello, wonderful World!";

		REQUIRE_THROWS_AS(s[420] = 'W', std::out_of_range);
		REQUIRE_THROWS_AS(sConst[420], std::out_of_range);
	}
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
