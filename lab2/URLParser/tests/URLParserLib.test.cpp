#define CATCH_CONFIG_MAIN
#include "../URLParserLib.h"
#include "catch.hpp"

TEST_CASE("URL parsing works correctly")
{
	SECTION("protocol is parsed correctly")
	{
		SECTION("valid protocol returns enum value")
		{
			REQUIRE(ParseProtocol("http") == Protocol::HTTP);
			REQUIRE(ParseProtocol("https") == Protocol::HTTPS);
			REQUIRE(ParseProtocol("ftp") == Protocol::FTP);
		}

		SECTION("empty or invalid protocol results in an exception")
		{
			REQUIRE_THROWS_AS(ParseProtocol(""), std::invalid_argument);
			REQUIRE_THROWS_AS(ParseProtocol("telnet"), std::invalid_argument);
		}
	}

	SECTION("host is parsed correctly")
	{
		SECTION("valid host returns the same value")
		{
			REQUIRE(ParseHost("github.com") == "github.com");
		}

		SECTION("invalid empty host results in an exception")
		{
			REQUIRE_THROWS_AS(ParseHost(""), std::invalid_argument);
		}
	}

	SECTION("port parsing works correctly")
	{
		SECTION("valid port is parsed correctly")
		{
			REQUIRE(ParsePort("42", Protocol::HTTP) == 42);
		}

		SECTION("empty port results in default value for specific protocol")
		{
			REQUIRE(ParsePort("", Protocol::HTTP) == 80);
			REQUIRE(ParsePort("", Protocol::HTTPS) == 443);
			REQUIRE(ParsePort("", Protocol::FTP) == 21);
		}

		SECTION("exceeding port value results in an error")
		{
			REQUIRE_THROWS_AS(ParsePort(std::to_string(MIN_PORT - 1), Protocol::HTTP), std::invalid_argument);
			REQUIRE_THROWS_AS(ParsePort(std::to_string(MAX_PORT + 1), Protocol::HTTP), std::invalid_argument);
		}

		SECTION("invalid port format results in an exception")
		{
			REQUIRE_THROWS_AS(ParsePort("not a port", Protocol::HTTP), std::invalid_argument);
		}
	}

	SECTION("overall URL parsing works correctly")
	{
		SECTION("valid URL is parsed correctly")
		{
			const std::string url = "https://github.com/m3tro1d";
			auto const info = ParseURL(url);

			REQUIRE(info.url == url);
			REQUIRE(info.protocol == Protocol::HTTPS);
			REQUIRE(info.host == "github.com");
			REQUIRE(info.port == 443);
			REQUIRE(info.document == "m3tro1d");
		}

		SECTION("empty document does not result in an error not depending on the slash at the end")
		{
			const std::string url = "https://github.com";
			auto const info = ParseURL(url);
			REQUIRE(info.document.empty());

			const std::string urlWithSlash = "https://github.com/";
			auto const infoWithSlash = ParseURL(urlWithSlash);
			REQUIRE(infoWithSlash.document.empty());
		}

		SECTION("invalid URL results in an exception")
		{
			const std::string url = "hello there";
			REQUIRE_THROWS_AS(ParseURL(url), std::invalid_argument);
		}
	}
}

TEST_CASE("printing out URL information works correctly")
{
	std::stringstream output;
	URLInfo info;
	info.url = "https://github.com/m3tro1d";
	info.protocol = Protocol::HTTPS;
	info.host = "github.com";
	info.port = 443;
	info.document = "m3tro1d";
	PrintURLInfo(output, info);

	REQUIRE(output.str() == "https://github.com/m3tro1d\nHOST: github.com\nPORT: 443\nDOC: m3tro1d\n");
}

TEST_CASE("stream processing works correctly")
{
	SECTION("valid URLs are printed as expected")
	{
		std::stringstream input("https://github.com/m3tro1d");
		std::stringstream output;
		ProcessURLs(input, output);

		REQUIRE(output.str() == "https://github.com/m3tro1d\nHOST: github.com\nPORT: 443\nDOC: m3tro1d\n");
	}

	SECTION("an error message is printed or invalid URLs")
	{
		std::stringstream input("hello there");
		std::stringstream output;
		ProcessURLs(input, output);

		REQUIRE(output.str() == "URL parsing error: invalid URL\n");
	}
}
