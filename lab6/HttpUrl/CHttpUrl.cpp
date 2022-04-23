#include "CHttpUrl.h"

#include <utility>

CHttpUrl::CHttpUrl(std::string const& url)
{
	// TODO: initialize fields with a regex
}

CHttpUrl::CHttpUrl(
	std::string domain,
	std::string document,
	CHttpUrl::Protocol protocol)
	: m_domain(std::move(domain))
	, m_document(std::move(document))
	, m_protocol(protocol)
	, m_port(GetPortForProtocol(protocol))
{
}

CHttpUrl::CHttpUrl(
	std::string domain,
	std::string document,
	CHttpUrl::Protocol protocol,
	CHttpUrl::Port port)
	: m_domain(std::move(domain))
	, m_document(std::move(document))
	, m_protocol(protocol)
	, m_port(port)
{
}

std::string CHttpUrl::GetURL() const
{
	// TODO: build URL by a template
	return {};
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

CHttpUrl::Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

CHttpUrl::Port CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::ProtocolToString(CHttpUrl::Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return "HTTP";
	case Protocol::HTTPS:
		return "HTTPS";
	default:
		return "";
	}
}

CHttpUrl::Port CHttpUrl::GetPortForProtocol(CHttpUrl::Protocol protocol)
{
	auto const result = DEFAULT_PORTS.find(protocol);
	if (result == DEFAULT_PORTS.end())
	{
		throw CUrlParsingError("no default port for protocol");
	}

	return result->second;
}
