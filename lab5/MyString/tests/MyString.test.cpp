#define CATCH_CONFIG_MAIN
#include "../CMyString.h"
#include "catch.hpp"

TEST_CASE("string creation")
{
	SECTION("empty string")
	{
		CMyString s;

		REQUIRE(std::strcmp(s.GetStringData(), "") == 0);
		REQUIRE(s.GetLength() == 0);
	}

	SECTION("using C string")
	{
		SECTION("valid C string is copied")
		{
			auto const cString = "Hello, wonderful World!";
			CMyString s(cString);

			REQUIRE(std::strcmp(s.GetStringData(), cString) == 0);
			REQUIRE(s.GetLength() == std::strlen(cString));
		}

		SECTION("null pointer results in an empty string")
		{
			CMyString s(nullptr);

			REQUIRE(std::strcmp(s.GetStringData(), "") == 0);
			REQUIRE(s.GetLength() == 0);
		}
	}

	SECTION("using char pointer and length")
	{
		SECTION("valid C string is copied")
		{
			auto const cString = "Hello, wonderful World!";
			size_t const length = 5;
			CMyString s(cString, length);

			REQUIRE(std::strcmp(s.GetStringData(), "Hello") == 0);
			REQUIRE(s.GetLength() == length);
		}

		SECTION("null pointer results in an empty string")
		{
			CMyString s(nullptr, 42);

			REQUIRE(std::strcmp(s.GetStringData(), "") == 0);
			REQUIRE(s.GetLength() == 0);
		}

		SECTION("null characters in the middle are ignored")
		{
			auto const cString = "Hello\0, wonderful\0 World!";
			size_t const length = 25;
			CMyString s(cString, length);

			REQUIRE(std::memcmp(s.GetStringData(), cString, length) == 0);
			REQUIRE(s.GetLength() == length);
		}
	}

	SECTION("using STL string")
	{
		SECTION("usual STL string is copied")
		{
			std::string const stlString = "Hello, wonderful World of C++ standard library!";
			CMyString s(stlString);

			REQUIRE(s.GetStringData() == stlString);
			REQUIRE(s.GetLength() == stlString.length());
		}

		SECTION("null characters in the middle are ignored")
		{
			size_t const length = 25;
			std::string const stlString("Hello\0, wonderful\0 World!", length);
			CMyString s(stlString);

			REQUIRE(std::memcmp(s.GetStringData(), stlString.c_str(), length) == 0);
			REQUIRE(s.GetLength() == length);
		}
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
		REQUIRE(CMyString("Hello, World!") == CMyString("Hello, World!"));
		REQUIRE_FALSE(CMyString("Hello, World!") == CMyString("Goodbye, World!"));
	}

	SECTION("inequality")
	{
		REQUIRE_FALSE(CMyString("Hello, World!") != CMyString("Hello, World!"));
		REQUIRE(CMyString("Hello, World!") != CMyString("Goodbye, World!"));
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
		std::stringstream output;

		SECTION("usual string")
		{
			std::string const originalString = "Hello, World!";
			CMyString s = originalString;
			output << s;

			REQUIRE(output.str() == originalString);
		}

		SECTION("containing null characters")
		{
			char const* originalString = "Hello\0, Worl\0d!";
			size_t const length = 15;
			CMyString s(originalString, length);
			output << s;

			REQUIRE(std::memcmp(output.str().c_str(), originalString, length) == 0);
		}
	}

	SECTION("reading")
	{
		// TODO
	}
}
