#define CATCH_CONFIG_MAIN
#include "../HTMLProcessor.h"
#include "catch.hpp"
#include <sstream>

TEST_CASE("encoded string is processed correctly")
{
	SECTION("empty string results in an empty result")
	{
		const std::string input;
		auto const decoded = HtmlDecode(input);

		REQUIRE(decoded.empty());
	}

		SECTION("string with no escape sequences is unchanged")
		{
			const std::string input = "so let it be written, so let it be done";
			auto const decoded = HtmlDecode(input);

			REQUIRE(decoded == input);
		}

	SECTION("string with only pattern start is unchanged")
	{
		const std::string input = "so let it be written & so let it be &; done";
		auto const decoded = HtmlDecode(input);

		REQUIRE(decoded == input);
	}

	SECTION("valid replace sequences are replaced correctly")
	{
		const std::string input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
		const std::string result = "Cat <says> \"Meow\". M&M's";
		auto const decoded = HtmlDecode(input);

		REQUIRE(decoded == result);
	}

	SECTION("invalid replace sequences are not replaced")
	{
		const std::string input = "Cat &lt;says&gt; &quotted;Meow&quot;. M&ampersand;M&apos;s";
		const std::string result = "Cat <says> &quotted;Meow\". M&ampersand;M's";
		auto const decoded = HtmlDecode(input);

		REQUIRE(decoded == result);
	}

	SECTION("doubling ampersand sequence is replaced correctly")
	{
		const std::string input = "&amp&lt;";
		const std::string result = "&amp<";
		auto const decoded = HtmlDecode(input);

		REQUIRE(decoded == result);
	}

	SECTION("stacked sequences are replaced correctly")
	{
		const std::string input = "&amp;&lt;";
		const std::string result = "&<";
		auto const decoded = HtmlDecode(input);

		REQUIRE(decoded == result);
	}

	SECTION("expanded valid sequences is not replaced")
	{
		const std::string input = "&amp;lt;";
		const std::string result = "&lt;";
		auto const decoded = HtmlDecode(input);

		REQUIRE(decoded == result);
	}
}

TEST_CASE("encoded stream with several lines is processed correctly")
{
	std::istringstream input("Cat &lt;says&gt;\n&quot;Meow&quot;. M&amp;M&apos;s");
	std::ostringstream output;
	const std::string result = "Cat <says>\n\"Meow\". M&M's\n";
	HtmlDecode(input, output);

	REQUIRE(output.str() == result);
}
