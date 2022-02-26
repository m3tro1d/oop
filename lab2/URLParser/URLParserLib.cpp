#include "URLParserLib.h"

Protocol ParseProtocol(const std::string& protocolString)
{
	if (protocolString == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocolString == "https")
	{
		return Protocol::HTTPS;
	}
	else if (protocolString == "ftp")
	{
		return Protocol::FTP;
	}

	throw std::invalid_argument("invalid protocol");
}

std::string ParseHost(const std::string& host)
{
	if (host.empty())
	{
		throw std::invalid_argument("empty host");
	}

	return host;
}

int ParsePort(const std::string& portString, Protocol protocol)
{
	if (portString.empty())
	{
		return DEFAULT_PORTS.at(protocol);
	}

	int port;
	try
	{
		port = std::stoi(portString);
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("invalid port");
	}

	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw std::invalid_argument("invalid port value");
	}

	return port;
}

URLInfo ParseURL(const std::string& url)
{
	std::regex urlRegex(
		R"((ftp|https?)://([0-9A-Za-z\-.]+)(?::(\d+))?(?:/(.*))?)",
		std::regex::icase);

	std::smatch matches;
	if (!std::regex_search(url, matches, urlRegex))
	{
		throw std::invalid_argument("invalid URL");
	}

	URLInfo result;
	result.url = url;
	result.protocol = ParseProtocol(matches[1].str());
	result.host = ParseHost(matches[2].str());
	result.port = ParsePort(matches[3].str(), result.protocol);
	result.document = matches[4].str();

	return result;
}

void PrintURLInfo(std::ostream& output, const URLInfo& urlInfo)
{
	output << urlInfo.url << '\n'
		   << "HOST: " << urlInfo.host << '\n'
		   << "PORT: " << urlInfo.port << '\n'
		   << "DOC: " << urlInfo.document << '\n';
}

void ProcessURLs(std::istream& input, std::ostream& output)
{
	std::string url;
	while (std::getline(input, url))
	{
		try
		{
			PrintURLInfo(output, ParseURL(url));
		}
		catch (const std::exception& e)
		{
			output << "URL parsing error: " << e.what() << '\n';
		}
	}
}
