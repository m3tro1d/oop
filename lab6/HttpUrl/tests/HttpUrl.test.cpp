#define CATCH_CONFIG_MAIN
#include "../CHttpUrl.h"
#include "catch.hpp"

TEST_CASE("constructing an URL")
{
	std::string const sourceUrl = "http://github.com/m3tro1d";
	std::string const sourceUrlWPort = "http://github.com:80/m3tro1d";
	std::string const sourceUrlWODocument = "http://github.com";
	std::string const domain = "github.com";
	std::string const document = "/m3tro1d";
	CHttpUrl::Protocol const protocol = CHttpUrl::Protocol::HTTP;
	CHttpUrl::Port const port = 80;

	SECTION("with all fields")
	{
		SECTION("with not empty document")
		{
			CHttpUrl url(domain, document, protocol, port);

			REQUIRE(url.GetDomain() == domain);
			REQUIRE(url.GetDocument() == document);
			REQUIRE(url.GetProtocol() == protocol);
			REQUIRE(url.GetPort() == port);
		}

		SECTION("with empty document")
		{
			CHttpUrl url(domain, "", protocol, port);

			REQUIRE(url.GetDocument() == "/");
		}

		SECTION("with document without leading slash")
		{
			CHttpUrl url(domain, "wut", protocol, port);

			REQUIRE(url.GetDocument() == "/wut");
		}
	}

	SECTION("without port")
	{
		SECTION("with https protocol")
		{
			CHttpUrl url(domain, document, CHttpUrl::Protocol::HTTPS);

			REQUIRE(url.GetDomain() == domain);
			REQUIRE(url.GetDocument() == document);
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 443);
		}

		SECTION("with not empty document")
		{
			CHttpUrl url(domain, document, protocol);

			REQUIRE(url.GetDomain() == domain);
			REQUIRE(url.GetDocument() == document);
			REQUIRE(url.GetProtocol() == protocol);
			REQUIRE(url.GetPort() == port);
		}

		SECTION("with empty document")
		{
			CHttpUrl url(domain, "", protocol);

			REQUIRE(url.GetDocument() == "/");
		}

		SECTION("with document without leading slash")
		{
			CHttpUrl url(domain, "wut", protocol);

			REQUIRE(url.GetDocument() == "/wut");
		}
	}

	SECTION("from a string")
	{
		SECTION("valid URL")
		{
			SECTION("with explicit port")
			{
				CHttpUrl url(sourceUrlWPort);

				REQUIRE(url.GetDomain() == domain);
				REQUIRE(url.GetDocument() == document);
				REQUIRE(url.GetProtocol() == protocol);
				REQUIRE(url.GetPort() == port);
			}

			SECTION("without port")
			{
				CHttpUrl url(sourceUrl);

				REQUIRE(url.GetDomain() == domain);
				REQUIRE(url.GetDocument() == document);
				REQUIRE(url.GetProtocol() == protocol);
				REQUIRE(url.GetPort() == port);
			}

			SECTION("without document")
			{
				CHttpUrl url(sourceUrlWODocument);

				REQUIRE(url.GetDomain() == domain);
				REQUIRE(url.GetDocument() == "/");
				REQUIRE(url.GetProtocol() == protocol);
				REQUIRE(url.GetPort() == port);
			}
		}

		SECTION("invalid URL")
		{
			SECTION("overall")
			{
				REQUIRE_THROWS_AS(CHttpUrl("wut"), CUrlParsingError);
			}

			SECTION("with empty domain")
			{
				REQUIRE_THROWS_AS(CHttpUrl("http:///whatever"), CUrlParsingError);
			}

			SECTION("with invalid port")
			{
				REQUIRE_THROWS_AS(CHttpUrl("http://github.com:alksjd/whatever"), CUrlParsingError);
			}

			SECTION("with out-of-range port")
			{
				REQUIRE_THROWS_AS(CHttpUrl("http://github.com:100000000000000000/whatever"), CUrlParsingError);
				REQUIRE_THROWS_AS(CHttpUrl("http://github.com:-1/whatever"), CUrlParsingError);
			}
		}
	}
}

TEST_CASE("building a string URL")
{
	std::string const sourceUrl = "http://github.com/m3tro1d";
	std::string const domain = "github.com";
	std::string const document = "/m3tro1d";
	CHttpUrl::Protocol const protocol = CHttpUrl::Protocol::HTTP;
	CHttpUrl::Port const port = 80;

	std::string const sourceUrlWCustomPort = "http://github.com:12/m3tro1d";
	CHttpUrl::Port const customPort = 12;

	std::string const sourceUrlWODocument = "http://github.com/";

	SECTION("with standard port")
	{
		CHttpUrl url(domain, document, protocol, port);

		REQUIRE(url.GetUrl() == sourceUrl);
	}

	SECTION("with non-standard port")
	{
		CHttpUrl url(domain, document, protocol, customPort);

		REQUIRE(url.GetUrl() == sourceUrlWCustomPort);
	}

	SECTION("with empty document")
	{
		CHttpUrl url(domain, "", protocol);

		REQUIRE(url.GetUrl() == sourceUrlWODocument);
	}
}

TEST_CASE("converting protocol to string")
{
	REQUIRE(CHttpUrl::ProtocolToString(CHttpUrl::Protocol::HTTP) == "http");
	REQUIRE(CHttpUrl::ProtocolToString(CHttpUrl::Protocol::HTTPS) == "https");
}
