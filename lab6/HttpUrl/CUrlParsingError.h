#pragma once

#include <stdexcept>

class CUrlParsingError : public std::invalid_argument
{
public:
	explicit CUrlParsingError(std::string const& message);
};
