#include "CHttpUrl.h"

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::regex urlRegex(
		R"((https?)://([0-9A-Za-z\-.]+)(?::(\d+))?(?:/(.*))?)",
		std::regex::icase);

	std::smatch matches;
	if (!std::regex_match(url, matches, urlRegex))
	{
		throw CUrlParsingError::InvalidUrlError();
	}

	m_domain = ParseDomain(matches[2]);
	m_document = ParseDocument(matches[4]);
	m_protocol = ParseProtocol(matches[1]);
	m_port = matches[3].str().empty() ? GetDefaultPort(m_protocol) : ParsePort(matches[3]);
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
	, m_document(ParseDocument(document))
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
	result += GetDocument();

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

std::string ToLower(std::string const& str)
{
	std::string result;
	std::transform(
		str.begin(),
		str.end(),
		std::back_inserter(result),
		[](char ch) {
			return std::tolower(ch);
		});
	return result;
}

CHttpUrl::Protocol CHttpUrl::ParseProtocol(std::string const& str)
{
	auto const lowerStr = ToLower(str);
	if (lowerStr == "http")
	{
		return Protocol::HTTP;
	}
	else if (lowerStr == "https")
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

	if (str.at(0) != '/')
	{
		return "/" + str;
	}

	return str;
}

CHttpUrl::Port CHttpUrl::ParsePort(std::string const& str)
{
	unsigned long port;
	try
	{
		port = std::stoul(str);
	}
	catch (std::invalid_argument const&)
	{
		throw CUrlParsingError::InvalidPortError();
	}
	catch (std::out_of_range const&)
	{
		throw CUrlParsingError::PortOutOfRangeError();
	}

	if (port < MIN_PORT || port > MAX_PORT)
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
