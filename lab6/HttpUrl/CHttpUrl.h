#pragma once

#include "CUrlParsingError.h"
#include <regex>
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

	CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		Port port);

	std::string GetUrl() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	Port GetPort() const;

	static std::string ProtocolToString(Protocol protocol);

private:
	static constexpr Port MIN_PORT = 1;
	static constexpr Port MAX_PORT = std::numeric_limits<Port>::max();

	static inline const std::unordered_map<Protocol, Port> DEFAULT_PORTS = {
		{ Protocol::HTTP, 80 },
		{ Protocol::HTTPS, 443 },
	};

	static Protocol ParseProtocol(std::string const& str);
	static std::string ParseDomain(std::string const& str);
	static std::string ParseDocument(std::string const& str);
	static Port ParsePort(std::string const& str);

	static Port GetDefaultPort(Protocol protocol);

	bool HasDefaultPort() const;

	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	Port m_port;
};
