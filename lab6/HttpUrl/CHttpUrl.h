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
	};
	using Port = unsigned short;

	explicit CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		Port port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	Port GetPort() const;

	static std::string ProtocolToString(Protocol protocol);

private:
	static inline const std::unordered_map<Protocol, Port> DEFAULT_PORTS = {
		{ Protocol::HTTP, 80 },
		{ Protocol::HTTPS, 443 },
	};

	static Port GetDefaultPort(Protocol protocol);
	bool HasDefaultPort() const;

	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	Port m_port;
};
