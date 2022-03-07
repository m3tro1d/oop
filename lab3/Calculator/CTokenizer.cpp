#include "CTokenizer.h"

Token CTokenizer::GetToken(std::istream& input)
{
	char ch = 0;
	double number;

	do
	{
		if (!input.get(ch))
		{
			return Token::END;
		}
	} while (ch == ' ');

	switch (ch)
	{
	case 0:
	case '\n':
		return Token::END;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		input.putback(ch);
		input >> number;
		return Token::NUMBER;

	case '+':
		return Token::PLUS;
	case '-':
		return Token::MINUS;
	case '*':
		return Token::MULTIPLY;
	case '/':
		return Token::DIVIDE;

	default:
		throw std::invalid_argument("invalid character");
	}
}
