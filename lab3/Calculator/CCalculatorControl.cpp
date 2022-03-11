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
			GetHandlerForExpression(expression.type)(expression.arguments);
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
	if (expression == "help")
	{
		return ExpressionType::HELP;
	}
	else if (expression == "exit")
	{
		return ExpressionType::EXIT;
	}
	else if (expression == "var")
	{
		return ExpressionType::CREATE_VARIABLE;
	}
	else if (expression == "let")
	{
		return ExpressionType::ASSIGN_VARIABLE;
	}
	else if (expression == "fn")
	{
		return ExpressionType::CREATE_FUNCTION;
	}
	else if (expression == "print")
	{
		return ExpressionType::PRINT_IDENTIFIER;
	}
	else if (expression == "printvars")
	{
		return ExpressionType::PRINT_VARIABLES;
	}
	else if (expression == "printfns")
	{
		return ExpressionType::PRINT_FUNCTIONS;
	}

	throw std::invalid_argument("invalid expression");
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
	m_output << "help                                                    show this message\n"
				"exit                                                    stop the program\n"
				"var [identifier]                                        create new variable\n"
				"let [identifier] = [number]                             assign number value to a variable\n"
				"let [identifier] = [identifier2]                        assign another variable to a variable\n"
				"fn [identifier] = [identifier2]                         create simple function\n"
				"fn [identifier] = [identifier2] [operand] [identifier3] create complex function\n"
				"print [identifier]                                      print the value of the identifier\n"
				"printvars                                               print all variables values\n"
				"printfns                                                print all functions values\n";
}

void CCalculatorControl::CreateVariable(const std::string& arguments)
{
	try
	{
		m_calculator.CreateVariable(arguments);
	}
	catch (const std::exception& e)
	{
		m_output << "Error: " << e.what() << '\n';
	}
}

void CCalculatorControl::AssignVariable(const std::string& arguments)
{
}

void CCalculatorControl::CreateFunction(const std::string& arguments)
{
}

void CCalculatorControl::PrintIdentifier(const std::string& arguments)
{
	try
	{
		m_output << std::fixed << std::setprecision(PRINT_PRECISION)
				 << m_calculator.GetIdentifierValue(arguments) << '\n';
	}
	catch (const std::exception& e)
	{
		m_output << "Error: " << e.what() << '\n';
	}
}

void CCalculatorControl::PrintVariables()
{
	auto const variables = m_calculator.DumpVariables();
	for (auto const& [variable, value] : variables)
	{
		m_output << variable << ':' << value << '\n';
	}
}

void CCalculatorControl::PrintFunctions()
{
	auto const functions = m_calculator.DumpFunctions();
	for (auto const& [function, value] : functions)
	{
		m_output << function << ':' << value << '\n';
	}
}
