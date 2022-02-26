#pragma once

#include <iostream>
#include <map>
#include <regex>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
};

constexpr int MIN_PORT = 1;
constexpr int MAX_PORT = 65535;

const std::map<Protocol, int> DEFAULT_PORTS = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
	{ Protocol::FTP, 21 },
};

struct URLInfo
{
	std::string url;
	Protocol protocol;
	std::string host;
	int port;
	std::string document;
};

Protocol ParseProtocol(const std::string& protocolString);

std::string ParseHost(const std::string& host);

int ParsePort(const std::string& portString, Protocol protocol);

URLInfo ParseURL(const std::string& url);

void PrintURLInfo(std::ostream& output, const URLInfo& urlInfo);

void ProcessURLs(std::istream& input, std::ostream& output);
