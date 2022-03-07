#pragma once

#include <iostream>
#include <stdexcept>

enum class Token
{
	IDENTIFIER,
	NUMBER,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,

	VARIABLE_DECLARATION,
	ASSIGNMENT,
	FUNCTION_DEFINITION,
	PRINT,
	VARIABLES_DUMP,
	FUNCTIONS_DUMP,

	IDLE,
	END,
};

class CTokenizer
{
public:
	Token GetToken(std::istream& input);
};
