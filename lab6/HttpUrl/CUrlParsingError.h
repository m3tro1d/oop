#pragma once

#include <stdexcept>

class CUrlParsingError : std::invalid_argument
{
public:
	explicit CUrlParsingError(std::string const& message);
};
