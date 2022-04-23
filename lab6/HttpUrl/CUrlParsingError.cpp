#include "CUrlParsingError.h"

CUrlParsingError CUrlParsingError::InvalidUrlError()
{
	return CUrlParsingError(INVALID_URL_ERROR_MESSAGE);
}

CUrlParsingError CUrlParsingError::InvalidProtocolError()
{
	return CUrlParsingError(INVALID_PROTOCOL_ERROR_MESSAGE);
}

CUrlParsingError CUrlParsingError::InvalidPortError()
{
	return CUrlParsingError(INVALID_PORT_ERROR_MESSAGE);
}

CUrlParsingError CUrlParsingError::PortOutOfRangeError()
{
	return CUrlParsingError(PORT_OUT_OF_RANGE_ERROR_MESSAGE);
}

CUrlParsingError::CUrlParsingError(std::string const& message)
	: std::invalid_argument(message)
{
}
