#pragma once

#include <stdexcept>

class CStringStackUnderflowError : public std::runtime_error
{
public:
	CStringStackUnderflowError();

private:
	static inline const std::string MESSAGE = "string stack underflow error";
};
