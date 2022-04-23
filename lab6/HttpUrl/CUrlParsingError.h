#pragma once

#include <stdexcept>

class CUrlParsingError : public std::invalid_argument
{
public:
	static CUrlParsingError InvalidUrlError();
	static CUrlParsingError InvalidProtocolError();
	static CUrlParsingError InvalidPortError();
	static CUrlParsingError PortOutOfRangeError();

private:
	static inline const std::string INVALID_URL_ERROR_MESSAGE = "invalid URL";
	static inline const std::string INVALID_PROTOCOL_ERROR_MESSAGE = "invalid protocol";
	static inline const std::string INVALID_PORT_ERROR_MESSAGE = "invalid port";
	static inline const std::string PORT_OUT_OF_RANGE_ERROR_MESSAGE = "port out of range";

	explicit CUrlParsingError(std::string const& message);
};
