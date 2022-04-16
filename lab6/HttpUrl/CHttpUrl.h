#pragma once

#include "CUrlParsingError.h"
#include <string>
#include <unordered_map>

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

	explicit CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string domain,
		std::string document,
		Protocol protocol = Protocol::HTTP);
	CHttpUrl(
		std::string domain,
		std::string document,
		Protocol protocol,
		Port port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	Port GetPort() const;

private:
	const std::unordered_map<Protocol, Port> DEFAULT_PORTS = {
		{ Protocol::HTTP, 80 },
		{ Protocol::HTTPS, 443 },
		{ Protocol::FTP, 21 },
	};

	Port GetPortForProtocol(Protocol protocol);

	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	Port m_port;
};
