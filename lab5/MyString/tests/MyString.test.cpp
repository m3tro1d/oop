#define CATCH_CONFIG_MAIN
#include "../CMyString.h"
#include "catch.hpp"

TEST_CASE("string creation")
{
	SECTION("empty string")
	{
		CMyString const s;

		REQUIRE(std::strcmp(s.GetStringData(), "") == 0);
		REQUIRE(s.GetLength() == 0);
	}

	SECTION("using C string")
	{
		SECTION("valid C string is copied")
		{
			auto const cString = "Hello, wonderful World!";
			CMyString const s(cString);

			REQUIRE(std::strcmp(s.GetStringData(), cString) == 0);
			REQUIRE(s.GetLength() == std::strlen(cString));
		}

		SECTION("null pointer results in an empty string")
		{
			CMyString const s(nullptr);

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
			CMyString const s(cString, length);

			REQUIRE(std::strcmp(s.GetStringData(), "Hello") == 0);
			REQUIRE(s.GetLength() == length);
		}

		SECTION("null pointer results in an empty string")
		{
			CMyString const s(nullptr, 42);

			REQUIRE(std::strcmp(s.GetStringData(), "") == 0);
			REQUIRE(s.GetLength() == 0);
		}

		SECTION("null characters in the middle are ignored")
		{
			auto const cString = "Hello\0, wonderful\0 World!";
			size_t const length = 25;
			CMyString const s(cString, length);

			REQUIRE(std::memcmp(s.GetStringData(), cString, length) == 0);
			REQUIRE(s.GetLength() == length);
		}
	}

	SECTION("using STL string")
	{
		SECTION("usual STL string is copied")
		{
			std::string const stlString = "Hello, wonderful World of C++ standard library!";
			CMyString const s(stlString);

			REQUIRE(s.GetStringData() == stlString);
			REQUIRE(s.GetLength() == stlString.length());
		}

		SECTION("null characters in the middle are ignored")
		{
			size_t const length = 25;
			std::string const stlString("Hello\0, wonderful\0 World!", length);
			CMyString const s(stlString);

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
			CMyString const copy(s);

			REQUIRE(std::strcmp(s.GetStringData(), copy.GetStringData()) == 0);
			REQUIRE(s.GetLength() == copy.GetLength());
		}

		SECTION("modifying the copy does not affect the original string")
		{
			char const* initialString = "Hello, wonderful World!";
			CMyString s = initialString;
			CMyString const copy(s);
			char* firstCharPtr = const_cast<char*>(copy.GetStringData());
			*firstCharPtr = 'B';

			REQUIRE(std::strcmp(s.GetStringData(), initialString) == 0);
			REQUIRE(std::strcmp(copy.GetStringData(), initialString) != 0);
		}

		SECTION("copying ignores null characters")
		{
			CMyString s = "Hello\0, wonderful NULL\0!";
			CMyString const copy(s);

			REQUIRE(std::strcmp(s.GetStringData(), copy.GetStringData()) == 0);
			REQUIRE(s.GetLength() == copy.GetLength());
		}
	}

	SECTION("moving")
	{
		SECTION("moved string contains the same string with the same length")
		{
			char const* initialString = "Hello, wonderful World!";
			size_t const initialLength = std::strlen(initialString);
			CMyString s = initialString;
			CMyString const moved(std::move(s));

			REQUIRE(std::strcmp(initialString, moved.GetStringData()) == 0);
			REQUIRE(initialLength == moved.GetLength());
		}

		SECTION("initial string is zeroed after moving")
		{
			CMyString s = "Hello, wonderful World!";
			CMyString const moved(std::move(s));

			REQUIRE(s.GetStringData() == nullptr);
			REQUIRE(s.GetLength() == 0);
		}
	}
}

TEST_CASE("string assignment")
{
	SECTION("copy assignment")
	{
		CMyString s = "Hello, wonderful World!";
		CMyString copy;
		copy = s;

		REQUIRE(std::strcmp(s.GetStringData(), copy.GetStringData()) == 0);
	}

	SECTION("move assignment")
	{
		char const* initialString = "Hello, wonderful World!";
		CMyString s = initialString;
		CMyString moved;
		moved = std::move(s);

		REQUIRE(std::strcmp(moved.GetStringData(), initialString) == 0);
		REQUIRE(s.GetStringData() == nullptr);
		REQUIRE(s.GetLength() == 0);
	}

	SECTION("self-assignment has no effect")
	{
		char const* initialString = "Hello, wonderful World!";
		CMyString s = initialString;
		size_t const initialLength = s.GetLength();

		s = s;
		REQUIRE(std::strcmp(s.GetStringData(), initialString) == 0);
		REQUIRE(s.GetLength() == initialLength);

		s = std::move(s);
		REQUIRE(std::strcmp(s.GetStringData(), initialString) == 0);
		REQUIRE(s.GetLength() == initialLength);
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

	SECTION("slicing ignores null characters")
	{
		CMyString sNulls = "Hello\0, wonderful\0 NULL!";
		size_t const start = 0;
		size_t const length = 8;

		auto const subString = sNulls.SubString(start, length);

		REQUIRE(std::strcmp(subString.GetStringData(), "Hello\0, ") == 0);
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

	// TODO: concatenation and check
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
		CMyString s1 = "Hello, ";
		CMyString const s2 = "World!";
		s1 += s2;

		REQUIRE(std::strcmp(s1.GetStringData(), "Hello, World!") == 0);
	}

	SECTION("plain concatenation")
	{
		CMyString const s1 = "Hello, ";
		CMyString const s2 = "World!";
		auto const result = s1 + s2;

		REQUIRE(std::strcmp(result.GetStringData(), "Hello, World!") == 0);
	}

	SECTION("null characters are ignored")
	{
		CMyString const s1("Hello\0, ", 8);
		CMyString const s2("World\0!", 7);
		auto const result = s1 + s2;

		REQUIRE(std::memcmp(result.GetStringData(), "Hello\0, World\0!", 15) == 0);
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
	SECTION("strict")
	{
		SECTION("less than")
		{
			REQUIRE(CMyString("122") < CMyString("123"));
			REQUIRE_FALSE(CMyString("123") < CMyString("12212"));
			REQUIRE_FALSE(CMyString("123") < CMyString("123"));
		}

		SECTION("greater than")
		{
			REQUIRE(CMyString("123") > CMyString("122"));
			REQUIRE_FALSE(CMyString("12212") > CMyString("123"));
			REQUIRE_FALSE(CMyString("123") > CMyString("123"));
		}
	}

	SECTION("not strict")
	{
		SECTION("less or equal to")
		{
			REQUIRE(CMyString("122") <= CMyString("123"));
			REQUIRE_FALSE(CMyString("123") <= CMyString("12212"));
			REQUIRE(CMyString("123") <= CMyString("123"));
		}

		SECTION("greater or equal to")
		{
			REQUIRE(CMyString("123") >= CMyString("122"));
			REQUIRE_FALSE(CMyString("12212") >= CMyString("123"));
			REQUIRE(CMyString("123") >= CMyString("123"));
		}
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
			CMyString const s = originalString;
			output << s;

			REQUIRE(output.str() == originalString);
		}

		SECTION("containing null characters")
		{
			char const* originalString = "Hello\0, Worl\0d!";
			size_t const length = 15;
			CMyString const s(originalString, length);
			output << s;

			REQUIRE(std::memcmp(output.str().c_str(), originalString, length) == 0);
		}
	}

	SECTION("reading")
	{
		std::stringstream input;

		SECTION("usual string")
		{
			char const* originalString = "Hello, World!";
			input.str(originalString);
			CMyString s;
			input >> s;

			REQUIRE(std::strcmp(s.GetStringData(), originalString) == 0);
		}

		SECTION("containing null characters")
		{
			std::string const originalString("Hello\0, Worl\0d!", 15);
			input.str(originalString);
			CMyString s;
			input >> s;

			REQUIRE(std::memcmp(s.GetStringData(), originalString.c_str(), 15) == 0);
		}

		SECTION("out of several lines only first one is read")
		{
			char const* originalString = "Hello\n, World\n!\n";
			input.str(originalString);
			CMyString s;
			input >> s;

			REQUIRE(std::strcmp(s.GetStringData(), "Hello") == 0);
		}
	}
}

TEST_CASE("string iterators")
{
	auto const initialString = "Hell\0o";
	size_t const initialLength = 6;

	CMyString s(initialString, initialLength);
	CMyString const sConst(initialString, initialLength);

	std::stringstream output;

	SECTION("straight")
	{
		SECTION("mutable")
		{
			SECTION("string is iterated from beginning to end")
			{
				for (auto it = s.begin(); it != s.end(); ++it)
				{
					output << *it;
				}
				REQUIRE(std::memcmp(output.str().c_str(), initialString, initialLength) == 0);
			}

			SECTION("string can be modified through an iterator")
			{
				auto it = s.begin();
				*it = 'W';
				for (it = s.begin(); it != s.end(); ++it)
				{
					output << *it;
				}
				REQUIRE(std::memcmp(output.str().c_str(), "Well\0o", initialLength) == 0);
			}

			SECTION("range-based loop is supported")
			{
				for (auto ch : s)
				{
					output << ch;
				}
				REQUIRE(std::memcmp(output.str().c_str(), initialString, initialLength) == 0);
			}
		}

		SECTION("const")
		{
			SECTION("string is iterated from beginning to end")
			{
				for (auto it = sConst.cbegin(); it != sConst.cend(); ++it)
				{
					output << *it;
				}
				REQUIRE(std::memcmp(output.str().c_str(), initialString, initialLength) == 0);
			}

			SECTION("range-based loop is supported")
			{
				for (auto ch : sConst)
				{
					output << ch;
				}
				REQUIRE(std::memcmp(output.str().c_str(), initialString, initialLength) == 0);
			}
		}
	}

	SECTION("reverse")
	{
		SECTION("mutable")
		{
			SECTION("string is iterated from end to beginning")
			{
				for (auto it = s.rbegin(); it != s.rend(); ++it)
				{
					output << *it;
				}
				REQUIRE(std::memcmp(output.str().c_str(), "o\0lleH", initialLength) == 0);
			}

			SECTION("string can be modified through an iterator")
			{
				auto it = s.rbegin();
				*it = 'W';
				for (it = s.rbegin(); it != s.rend(); ++it)
				{
					output << *it;
				}
				REQUIRE(std::memcmp(output.str().c_str(), "W\0lleH", initialLength) == 0);
			}
		}

		SECTION("const")
		{
			SECTION("string is iterated from end to beginning")
			{
				for (auto it = sConst.crbegin(); it != sConst.crend(); ++it)
				{
					output << *it;
				}
				REQUIRE(std::memcmp(output.str().c_str(), "o\0lleH", initialLength) == 0);
			}
		}
	}

	SECTION("difference between iterators")
	{
		auto begin = s.begin();
		auto end = s.end();
		REQUIRE(end - begin == initialLength);
	}

	SECTION("discrete access through iterator")
	{
		auto begin = s.begin();
		REQUIRE(begin[1] == 'e');

		begin[1] = 'o';
		REQUIRE(std::memcmp(s.GetStringData(), "Holl\0o", initialLength) == 0);
	}
}
