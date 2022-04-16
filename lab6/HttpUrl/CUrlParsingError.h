#pragma once

#include <stdexcept>

class CUrlParsingError : std::invalid_argument
{
public:
	// TODO: think of a better and more flexible system with
	//       error codes and separate messages
	//       for different types of errors
	explicit CUrlParsingError(std::string const& message);
};
