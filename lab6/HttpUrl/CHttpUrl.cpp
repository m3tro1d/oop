#include "CHttpUrl.h"

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::regex urlRegex(
		R"((https?)://(0-9A-Za-z\-.)(?::(\d+))?(?:/(.*))?)",
		std::regex::icase);

	std::smatch matches;
	if (!std::regex_match(url, matches, urlRegex))
	{
		throw CUrlParsingError::InvalidUrlError();
	}

	m_domain = ParseDomain(matches[1]);
	m_document = ParseDocument(matches[3]);
	m_protocol = ParseProtocol(matches[0]);
	m_port = ParsePort(matches[2]);
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	CHttpUrl::Protocol protocol)
	: CHttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	CHttpUrl::Protocol protocol,
	CHttpUrl::Port port)
	: m_domain(ParseDomain(domain))
	, m_document(document)
	, m_protocol(protocol)
	, m_port(port)
{
}

std::string CHttpUrl::GetUrl() const
{
	std::string result = ProtocolToString(GetProtocol());
	result += "://";
	result += GetDomain();
	result += HasDefaultPort() ? "" : ":" + std::to_string(GetPort());
	result += "/" + GetDocument();

	return result;
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
		return "http";
	case Protocol::HTTPS:
		return "https";
	default:
		throw std::runtime_error("no string value for protocol");
	}
}

CHttpUrl::Protocol CHttpUrl::ParseProtocol(std::string const& str)
{
	if (str == "http")
	{
		return Protocol::HTTP;
	}
	else if (str == "https")
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError::InvalidProtocolError();
}

std::string CHttpUrl::ParseDomain(const std::string& str)
{
	if (str.empty())
	{
		throw CUrlParsingError::InvalidUrlError();
	}

	return str;
}

std::string CHttpUrl::ParseDocument(const std::string& str)
{
	if (str.empty())
	{
		return "/";
	}

	return str;
}

CHttpUrl::Port CHttpUrl::ParsePort(std::string const& str)
{
	int port;
	try
	{
		port = std::stoi(str);
	}
	catch (std::invalid_argument const&)
	{
		throw CUrlParsingError::InvalidPortError();
	}
	catch (std::out_of_range const&)
	{
		throw CUrlParsingError::PortOutOfRangeError();
	}

	if (port < std::numeric_limits<Port>::min() || port > std::numeric_limits<Port>::max())
	{
		throw CUrlParsingError::PortOutOfRangeError();
	}

	return static_cast<Port>(port);
}

CHttpUrl::Port CHttpUrl::GetDefaultPort(CHttpUrl::Protocol protocol)
{
	auto const result = DEFAULT_PORTS.find(protocol);
	if (result == DEFAULT_PORTS.end())
	{
		throw std::runtime_error("no default port for protocol");
	}

	return result->second;
}

bool CHttpUrl::HasDefaultPort() const
{
	return DEFAULT_PORTS.find(GetProtocol())->second == GetPort();
}
