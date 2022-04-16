#pragma once

#include <string>

class CHttpUrl
{
public:
	enum class Protocol
	{
		HTTP,
		HTTPS,
		FTP,
	};
	using Port = unsigned short;

	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol = Protocol::HTTP);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, Port port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	Port GetPort() const;

private:
	Protocol protocol;
	std::string domain;
	std::string document;
	Port port;
};
