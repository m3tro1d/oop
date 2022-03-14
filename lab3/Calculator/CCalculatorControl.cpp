#include "CCalculatorControl.h"

CCalculatorControl::CCalculatorControl(std::istream& input, std::ostream& output, CCalculator& calculator)
	: m_input(input)
	, m_output(output)
	, m_calculator(calculator)
{
}

void CCalculatorControl::StartControl()
{
	bool finished = false;

	while (!finished)
	{
		m_output << PROMPT;
		auto const expression = ReadExpression();
		switch (expression.type)
		{
		case ExpressionType::HELP:
		case ExpressionType::CREATE_VARIABLE:
		case ExpressionType::ASSIGN_VARIABLE:
		case ExpressionType::CREATE_FUNCTION:
		case ExpressionType::PRINT_IDENTIFIER:
		case ExpressionType::PRINT_VARIABLES:
		case ExpressionType::PRINT_FUNCTIONS:
			WrapWithExceptionHandling(GetHandlerForExpression(expression.type), expression.arguments);
			break;
		case ExpressionType::EXIT:
			finished = true;
			m_output << "Farewell!\n";
			break;
		default:
			break;
		}
	}
}

CCalculatorControl::Expression CCalculatorControl::ReadExpression()
{
	std::string userInput;
	std::string arguments;
	std::getline(m_input, userInput);
	std::stringstream input(userInput);

	ExpressionType type = ExpressionType::IDLE;
	std::string expressionTypeStr;
	try
	{
		std::getline(input, expressionTypeStr, ' ');
		if (!std::getline(input, arguments))
		{
			arguments.clear();
		}
		type = ParseExpressionType(expressionTypeStr);
	}
	catch (const std::exception& e)
	{
		m_output << "Error: " << e.what() << '\n';
	}

	return {
		.type = type,
		.arguments = arguments,
	};
}

CCalculatorControl::ExpressionType CCalculatorControl::ParseExpressionType(const std::string& expression)
{
	auto const type = EXPRESSION_KEYWORDS.find(expression);
	if (type == EXPRESSION_KEYWORDS.end())
	{
		throw std::invalid_argument("invalid expression");
	}

	return type->second;
}

CCalculatorControl::ExpressionHandler CCalculatorControl::GetHandlerForExpression(CCalculatorControl::ExpressionType expression)
{
	switch (expression)
	{
	case ExpressionType::HELP:
		return [this](const std::string&) {
			PrintHelp();
		};
	case ExpressionType::CREATE_VARIABLE:
		return [this](const std::string& arguments) {
			CreateVariable(arguments);
		};
	case ExpressionType::ASSIGN_VARIABLE:
		return [this](const std::string& arguments) {
			AssignVariable(arguments);
		};
	case ExpressionType::CREATE_FUNCTION:
		return [this](const std::string& arguments) {
			CreateFunction(arguments);
		};
	case ExpressionType::PRINT_IDENTIFIER:
		return [this](const std::string& arguments) {
			PrintIdentifier(arguments);
		};
	case ExpressionType::PRINT_VARIABLES:
		return [this](const std::string&) {
			PrintVariables();
		};
	case ExpressionType::PRINT_FUNCTIONS:
		return [this](const std::string&) {
			PrintFunctions();
		};
	default:
		throw std::invalid_argument("no handler for expression");
	}
}

void CCalculatorControl::PrintHelp()
{
	m_output << "help                                                     show this message\n"
				"exit                                                     stop the program\n"
				"var [identifier]                                         create new variable\n"
				"let [identifier] = [number]                              assign number value to a variable\n"
				"let [identifier] = [identifier2]                         assign another variable to a variable\n"
				"fn [identifier] = [identifier2]                          create simple function\n"
				"fn [identifier] = [identifier2] [operator] [identifier3] create complex function\n"
				"print [identifier]                                       print the value of the identifier\n"
				"printvars                                                print all variables values\n"
				"printfns                                                 print all functions values\n";
}

void CCalculatorControl::CreateVariable(const std::string& arguments)
{
	m_calculator.CreateVariable(arguments);
}

void CCalculatorControl::AssignVariable(const std::string& arguments)
{
	auto const identifier = GetIdentifierFromExpression(arguments);
	auto const assignment = ParseAssignment(arguments);

	if (std::holds_alternative<CCalculator::Identifier>(assignment))
	{
		m_calculator.AssignVariable(identifier, std::get<CCalculator::Identifier>(assignment));
	}
	else if (std::holds_alternative<CCalculator::Value>(assignment))
	{
		m_calculator.AssignVariable(identifier, std::get<CCalculator::Value>(assignment));
	}
	else
	{
		throw std::runtime_error("failed to parse assignment");
	}
}

void CCalculatorControl::CreateFunction(const std::string& arguments)
{
	auto const identifier = GetIdentifierFromExpression(arguments);
	auto const expression = ParseExpression(arguments);

	if (std::holds_alternative<CCalculator::Identifier>(expression))
	{
		m_calculator.CreateFunction(identifier, std::get<CCalculator::Identifier>(expression));
	}
	else if (std::holds_alternative<CCalculator::Expression>(expression))
	{
		m_calculator.CreateFunction(identifier, std::get<CCalculator::Expression>(expression));
	}
	else
	{
		throw std::runtime_error("failed to parse expression");
	}
}

void CCalculatorControl::PrintIdentifier(const std::string& arguments)
{
	PrepareForValuePrinting();
	m_output << m_calculator.GetIdentifierValue(arguments) << '\n';
}

void CCalculatorControl::PrintVariables()
{
	PrepareForValuePrinting();
	auto const variables = m_calculator.DumpVariables();
	for (auto const& [variable, value] : variables)
	{
		m_output << variable << ':' << value << '\n';
	}
}

void CCalculatorControl::PrintFunctions()
{
	PrepareForValuePrinting();
	auto const functions = m_calculator.DumpFunctions();
	for (auto const& [function, value] : functions)
	{
		m_output << function << ':' << value << '\n';
	}
}

void CCalculatorControl::PrepareForValuePrinting()
{
	m_output << std::fixed << std::setprecision(PRINT_PRECISION);
}

void CCalculatorControl::WrapWithExceptionHandling(const ExpressionHandler& handler, const std::string& arguments)
{
	try
	{
		handler(arguments);
	}
	catch (const std::exception& e)
	{
		m_output << "Error: " << e.what() << '\n';
	}
}

CCalculator::Identifier CCalculatorControl::GetIdentifierFromExpression(const std::string& expression)
{
	std::stringstream expressionStream(expression);
	std::string identifier;
	if (!std::getline(expressionStream, identifier, '='))
	{
		throw std::invalid_argument("no identifier provided");
	}

	Trim(identifier);
	if (identifier.empty())
	{
		throw std::invalid_argument("empty identifier");
	}

	return identifier;
}

std::variant<CCalculator::Identifier, CCalculator::Value> CCalculatorControl::ParseAssignment(const std::string& assignment)
{
	std::stringstream expressionStream(assignment);
	expressionStream.ignore(std::numeric_limits<std::streamsize>::max(), '=');
	std::string result;

	expressionStream >> result;
	if (result.empty())
	{
		throw std::invalid_argument("empty assignment");
	}

	try
	{
		return std::stod(result);
	}
	catch (const std::invalid_argument&)
	{
		return result;
	}
}

std::variant<CCalculator::Identifier, CCalculator::Expression> CCalculatorControl::ParseExpression(const std::string& expression)
{
	std::stringstream expressionStream(expression);
	expressionStream.ignore(std::numeric_limits<std::streamsize>::max(), '=');

	std::string operand1;
	char operatorCharacter = ' ';
	std::string operand2;

	expressionStream >> operand1;
	if (operand1.empty())
	{
		throw std::invalid_argument("invalid expression");
	}
	if (expressionStream.eof())
	{
		return operand1;
	}

	expressionStream >> operatorCharacter;
	if (operatorCharacter == ' ')
	{
		throw std::invalid_argument("invalid expression");
	}

	expressionStream >> operand2;
	if (operand2.empty())
	{
		throw std::invalid_argument("invalid expression");
	}

	return CCalculator::Expression{
		.operation = CharToOperator(operatorCharacter),
		.arguments = { operand1, operand2 },
	};
}

CCalculator::Operation CCalculatorControl::CharToOperator(char op)
{
	switch (op)
	{
	case '+':
		return CCalculator::Operation::ADDITION;
	case '-':
		return CCalculator::Operation::SUBTRACTION;
	case '*':
		return CCalculator::Operation::MULTIPLICATION;
	case '/':
		return CCalculator::Operation::DIVISION;
	default:
		throw std::invalid_argument("unknown operator");
	}
}
