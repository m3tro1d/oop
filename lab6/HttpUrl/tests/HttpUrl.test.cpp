#define CATCH_CONFIG_MAIN
#include "../CHttpUrl.h"
#include "catch.hpp"

TEST_CASE("constructing an URL")
{
	std::string const sourceUrl = "http://github.com/m3tro1d";
	std::string const domain = "github.com";
	std::string const document = "/m3tro1d";
	CHttpUrl::Protocol const protocol = CHttpUrl::Protocol::HTTP;
	CHttpUrl::Port const port = 80;

	SECTION("with all fields")
	{
		CHttpUrl url(domain, document, protocol, port);

		REQUIRE(url.GetDomain() == domain);
		REQUIRE(url.GetDocument() == document);
		REQUIRE(url.GetProtocol() == protocol);
		REQUIRE(url.GetPort() == port);
	}

	SECTION("without port")
	{
		SECTION("with http protocol")
		{
			CHttpUrl url(domain, document);

			REQUIRE(url.GetDomain() == domain);
			REQUIRE(url.GetDocument() == document);
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
			REQUIRE(url.GetPort() == 80);
		}

		SECTION("with https protocol")
		{
			CHttpUrl url(domain, document, CHttpUrl::Protocol::HTTPS);

			REQUIRE(url.GetDomain() == domain);
			REQUIRE(url.GetDocument() == document);
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 443);
		}
	}

	SECTION("with empty domain")
	{
		REQUIRE_THROWS_AS(CHttpUrl("", document, protocol, port), CUrlParsingError);
	}

	SECTION("from a string")
	{
		SECTION("valid URL")
		{
			SECTION("without port")
			{
				// TODO
			}

			SECTION("with port")
			{
				// TODO
			}
		}

		SECTION("invalid URL")
		{
			// TODO
		}
	}
}

TEST_CASE("building a string URL")
{
	std::string const sourceUrl = "http://github.com/m3tro1d";
	std::string const sourceUrl1 = "http://github.com:69/m3tro1d";
	std::string const domain = "github.com";
	std::string const document = "/m3tro1d";
	CHttpUrl::Protocol const protocol = CHttpUrl::Protocol::HTTP;
	CHttpUrl::Port const port = 80;
	CHttpUrl::Port const port1 = 69;

	SECTION("with default port")
	{
		CHttpUrl url(domain, document, protocol, port);

		REQUIRE(url.GetUrl() == sourceUrl);
	}

	SECTION("with custom port")
	{
		CHttpUrl url(domain, document, protocol, port1);

		REQUIRE(url.GetUrl() == sourceUrl1);
	}
}
