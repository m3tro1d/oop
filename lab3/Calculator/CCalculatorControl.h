#pragma once

#include "CCalculator.h"
#include "StringLib.h"
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <variant>

class CCalculatorControl
{
public:
	CCalculatorControl(std::istream& input, std::ostream& output, CCalculator& calculator);
	void StartControl();

private:
	const std::string PROMPT = "$ ";
	static constexpr int PRINT_PRECISION = 2;

	enum class ExpressionType
	{
		IDLE,
		HELP,
		EXIT,
		CREATE_VARIABLE,
		ASSIGN_VARIABLE,
		CREATE_FUNCTION,
		PRINT_IDENTIFIER,
		PRINT_VARIABLES,
		PRINT_FUNCTIONS,
	};

	struct Expression
	{
		ExpressionType type;
		std::string arguments;
	};

	using ExpressionHandler = std::function<void(const std::string& argument)>;

	const std::map<std::string, ExpressionType> EXPRESSION_KEYWORDS = {
		{ "help", ExpressionType::HELP },
		{ "exit", ExpressionType::EXIT },
		{ "var", ExpressionType::CREATE_VARIABLE },
		{ "let", ExpressionType::ASSIGN_VARIABLE },
		{ "fn", ExpressionType::CREATE_FUNCTION },
		{ "print", ExpressionType::PRINT_IDENTIFIER },
		{ "printvars", ExpressionType::PRINT_VARIABLES },
		{ "printfns", ExpressionType::PRINT_FUNCTIONS },
	};

	Expression ReadExpression();
	ExpressionType ParseExpressionType(const std::string& expression);
	ExpressionHandler GetHandlerForExpression(ExpressionType expression);

	void PrintHelp();
	void CreateVariable(const std::string& arguments);
	void AssignVariable(const std::string& arguments);
	void CreateFunction(const std::string& arguments);
	void PrintIdentifier(const std::string& arguments);
	void PrintVariables();
	void PrintFunctions();

	void PrepareForValuePrinting();

	void WrapWithExceptionHandling(const ExpressionHandler& handler, const std::string& arguments);

	static CCalculator::Identifier GetIdentifierFromExpression(const std::string& expression);
	static std::variant<CCalculator::Identifier, CCalculator::Value> ParseAssignment(const std::string& assignment);
	static std::variant<CCalculator::Identifier, CCalculator::Expression> ParseExpression(const std::string& expression);

	static CCalculator::Operation CharToOperator(char op);

	std::istream& m_input;
	std::ostream& m_output;
	CCalculator& m_calculator;
};
