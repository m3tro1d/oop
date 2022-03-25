#define CATCH_CONFIG_MAIN
#include "../CCalculator.h"
#include "../CCalculatorControl.h"
#include "catch.hpp"

bool ApproximatelyEquals(double a, double b)
{
	return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

TEST_CASE("base calculator works correctly")
{
	CCalculator calculator;

	SECTION("variables work correctly")
	{
		SECTION("variable creation works correctly")
		{
			SECTION("using non-existing and valid identifier creates a variable with NAN value")
			{
				const CCalculator::Identifier identifier = "test_123";
				calculator.CreateVariable(identifier);
				auto const variables = calculator.DumpVariables();
				REQUIRE(std::isnan(variables.at(identifier)));
			}

			SECTION("invalid identifier results in an error")
			{
				SECTION("identifier with invalid symbols")
				{
					const CCalculator::Identifier identifier = "tes%t";
					REQUIRE_THROWS_AS(
						calculator.CreateVariable(identifier),
						std::invalid_argument);
				}

				SECTION("identifier starting with number")
				{
					const CCalculator::Identifier identifier = "123test";
					REQUIRE_THROWS_AS(
						calculator.CreateVariable(identifier),
						std::invalid_argument);
				}
			}

			SECTION("creating variable with existing identifier results in an error")
			{
				const CCalculator::Identifier identifier = "test_123";
				calculator.CreateVariable(identifier);
				REQUIRE_THROWS_AS(
					calculator.CreateVariable(identifier),
					std::runtime_error);
				REQUIRE(calculator.DumpVariables().size() == 1);
			}
		}

		SECTION("variable assignment with value works correctly")
		{
			SECTION("assigning to an existing variable works correctly")
			{
				const CCalculator::Identifier identifier = "test_123";
				const CCalculator::Value value = 42.36;
				calculator.CreateVariable(identifier);
				calculator.AssignVariable(identifier, value);
				auto const variables = calculator.DumpVariables();
				REQUIRE(variables.at(identifier) == value);
			}

			SECTION("assigning to a non-existing variable works correctly")
			{
				const CCalculator::Identifier identifier = "test_123";
				const CCalculator::Value value = 42.36;
				calculator.AssignVariable(identifier, value);
				auto const variables = calculator.DumpVariables();
				REQUIRE(variables.at(identifier) == value);
			}
		}

		SECTION("variable assignment with identifier works correctly")
		{
			SECTION("assigning an existing identifier works correctly")
			{
				const CCalculator::Identifier identifier1 = "test_123";
				const CCalculator::Value value = 42.36;
				calculator.AssignVariable(identifier1, value);

				const CCalculator::Identifier identifier2 = "copy1";
				calculator.AssignVariable(identifier2, identifier1);

				auto const variables = calculator.DumpVariables();
				REQUIRE(variables.at(identifier2) == variables.at(identifier1));
			}

			SECTION("identifier value is copied in the variable")
			{
				const CCalculator::Identifier identifier1 = "test_123";
				const CCalculator::Value value = 42;
				calculator.AssignVariable(identifier1, value);

				const CCalculator::Identifier identifier2 = "copy1";
				calculator.AssignVariable(identifier2, identifier1);
				const CCalculator::Value newValue = 42;
				calculator.AssignVariable(identifier1, newValue);

				auto const variables = calculator.DumpVariables();
				REQUIRE(variables.at(identifier1) == newValue);
				REQUIRE(variables.at(identifier2) == value);
			}

			SECTION("assigning a non-existing identifier results in an error")
			{
				const CCalculator::Identifier identifier1 = "test_123";
				const CCalculator::Identifier identifier2 = "copy1";
				REQUIRE_THROWS_AS(
					calculator.AssignVariable(identifier2, identifier1),
					std::runtime_error);
			}
		}
	}

	SECTION("functions work correctly")
	{
		SECTION("function with one variable works correctly")
		{
			const CCalculator::Identifier var = "var";
			const CCalculator::Value value = 12.3;
			calculator.AssignVariable(var, value);

			const CCalculator::Identifier function = "function";
			calculator.CreateFunction(function, var);

			auto const functions = calculator.DumpFunctions();
			REQUIRE(functions.at(function) == value);
		}

		SECTION("function with variables creation works correctly")
		{
			const CCalculator::Identifier var1 = "var1";
			const CCalculator::Value value1 = 12.3;
			const CCalculator::Identifier var2 = "var2";
			const CCalculator::Value value2 = 45;
			calculator.AssignVariable(var1, value1);
			calculator.AssignVariable(var2, value2);

			const CCalculator::Identifier function = "function";
			const CCalculator::Expression expression = {
				.operation = CCalculator::Operation::ADDITION,
				.arguments = { var1, var2 },
			};
			calculator.CreateFunction(function, expression);

			auto const functions = calculator.DumpFunctions();
			REQUIRE(ApproximatelyEquals(functions.at(function), value1 + value2));
		}

		SECTION("function holds a reference to a variable, not a copy")
		{
			const CCalculator::Identifier var = "var";
			calculator.AssignVariable(var, 42);

			const CCalculator::Identifier function = "function";
			calculator.CreateFunction(function, var);

			const CCalculator::Value newValue = 43;
			calculator.AssignVariable(var, newValue);

			auto const functions = calculator.DumpFunctions();
			REQUIRE(functions.at(function) == newValue);
		}

		SECTION("function with other functions creation works correctly")
		{
			SECTION("function with a variable and a function is calculated correctly")
			{
				const CCalculator::Identifier var1 = "var1";
				const CCalculator::Value value1 = 12.3;
				const CCalculator::Identifier var2 = "var2";
				const CCalculator::Value value2 = 45;
				calculator.AssignVariable(var1, value1);
				calculator.AssignVariable(var2, value2);

				const CCalculator::Identifier argFun = "argFun";
				const CCalculator::Expression argExpression = {
					.operation = CCalculator::Operation::ADDITION,
					.arguments = { var1, var2 },
				};
				calculator.CreateFunction(argFun, argExpression);

				const CCalculator::Identifier argVar = "argVar";
				const CCalculator::Value argValue = 42.78;
				calculator.AssignVariable(argVar, argValue);

				const CCalculator::Identifier function = "function";
				const CCalculator::Expression expression = {
					.operation = CCalculator::Operation::DIVISION,
					.arguments = { argFun, argVar },
				};
				calculator.CreateFunction(function, expression);

				auto const functions = calculator.DumpFunctions();
				REQUIRE(ApproximatelyEquals(
					functions.at(function),
					(value1 + value2) / argValue));
			}

			SECTION("function with both function arguments is calculated correctly")
			{
				const CCalculator::Identifier var11 = "var11";
				const CCalculator::Value value11 = 12.3;
				const CCalculator::Identifier var12 = "var12";
				const CCalculator::Value value12 = 45;
				calculator.AssignVariable(var11, value11);
				calculator.AssignVariable(var12, value12);

				const CCalculator::Identifier f1 = "f1";
				const CCalculator::Expression e1 = {
					.operation = CCalculator::Operation::DIVISION,
					.arguments = { var11, var12 },
				};
				calculator.CreateFunction(f1, e1);

				const CCalculator::Identifier var21 = "var21";
				const CCalculator::Value value21 = 1000;
				const CCalculator::Identifier var22 = "var22";
				const CCalculator::Value value22 = 500.6;
				calculator.AssignVariable(var21, value21);
				calculator.AssignVariable(var22, value22);

				const CCalculator::Identifier f2 = "f2";
				const CCalculator::Expression e2 = {
					.operation = CCalculator::Operation::SUBTRACTION,
					.arguments = { var21, var22 },
				};
				calculator.CreateFunction(f2, e2);

				const CCalculator::Identifier function = "function";
				const CCalculator::Expression expression = {
					.operation = CCalculator::Operation::MULTIPLICATION,
					.arguments = { f1, f2 },
				};
				calculator.CreateFunction(function, expression);

				auto const functions = calculator.DumpFunctions();
				REQUIRE(ApproximatelyEquals(
					functions.at(function),
					(value11 / value12) * (value21 - value22)));
			}
		}

		SECTION("creating a function with expression containing non-existing identifiers results in an error")
		{
			SECTION("single identifier")
			{
				const CCalculator::Identifier var = "var";
				const CCalculator::Identifier function = "function";
				REQUIRE_THROWS_AS(calculator.CreateFunction(function, var), std::runtime_error);
			}

			SECTION("two identifiers")
			{
				const CCalculator::Identifier var1 = "var1";
				const CCalculator::Identifier var2 = "var2";

				const CCalculator::Identifier function = "function";
				const CCalculator::Expression expression = {
					.operation = CCalculator::Operation::ADDITION,
					.arguments = { var1, var2 },
				};

				REQUIRE_THROWS_AS(calculator.CreateFunction(function, expression), std::runtime_error);
			}
		}

		SECTION("calculating function with zero division returns nan")
		{
			const CCalculator::Identifier var1 = "var1";
			const CCalculator::Value value1 = 12.3;
			const CCalculator::Identifier var2 = "var2";
			const CCalculator::Value value2 = 0;
			calculator.AssignVariable(var1, value1);
			calculator.AssignVariable(var2, value2);

			const CCalculator::Identifier function = "function";
			const CCalculator::Expression expression = {
				.operation = CCalculator::Operation::DIVISION,
				.arguments = { var1, var2 },
			};
			calculator.CreateFunction(function, expression);

			auto const functions = calculator.DumpFunctions();
			REQUIRE(std::isnan(functions.at(function)));
		}

		SECTION("creating function with existing identifier results in an error")
		{
			SECTION("variable identifier")
			{
				const CCalculator::Identifier identifier = "test";
				const CCalculator::Expression expression = {
					.operation = CCalculator::Operation::ADDITION,
					.arguments = { "one", "two" },
				};
				calculator.CreateVariable(identifier);

				REQUIRE_THROWS_AS(
					calculator.CreateFunction(identifier, expression),
					std::runtime_error);
			}

			SECTION("function identifier")
			{
				const CCalculator::Identifier one = "one";
				const CCalculator::Identifier two = "two";
				calculator.CreateVariable(one);
				calculator.CreateVariable(two);

				const CCalculator::Identifier identifier = "test";
				const CCalculator::Expression expression = {
					.operation = CCalculator::Operation::ADDITION,
					.arguments = { "one", "two" },
				};
				calculator.CreateFunction(identifier, expression);

				REQUIRE_THROWS_AS(
					calculator.CreateFunction(identifier, expression),
					std::runtime_error);
			}
		}

		SECTION("operations with nan result in nan")
		{
			const CCalculator::Identifier var1 = "var1";
			const CCalculator::Value value1 = 12.3;
			const CCalculator::Identifier var2 = "var2";
			calculator.AssignVariable(var1, value1);
			calculator.CreateVariable(var2);

			const CCalculator::Identifier function = "function";
			const CCalculator::Expression expression = {
				.operation = CCalculator::Operation::ADDITION,
				.arguments = { var1, var2 },
			};
			calculator.CreateFunction(function, expression);

			auto const functions = calculator.DumpFunctions();
			REQUIRE(std::isnan(functions.at(function)));
		}
	}

	SECTION("getting identifier value works correctly")
	{
		SECTION("variable value returns correctly")
		{
			SECTION("getting existing but not assigned variable returns nan")
			{
				const CCalculator::Identifier identifier = "test";
				calculator.CreateVariable(identifier);
				REQUIRE(std::isnan(calculator.GetIdentifierValue("test")));
			}

			SECTION("getting existing variable returns it's value")
			{
				const CCalculator::Identifier identifier = "test";
				const CCalculator::Value value = 12.3;
				calculator.AssignVariable(identifier, value);
				REQUIRE(calculator.GetIdentifierValue(identifier) == value);
			}

			SECTION("getting non-existing variable results in an error")
			{
				REQUIRE_THROWS_AS(
					calculator.GetIdentifierValue("whatever"),
					std::runtime_error);
			}
		}

		SECTION("function value returns correctly")
		{
			const CCalculator::Identifier var1 = "var1";
			const CCalculator::Value value1 = 12.3;
			const CCalculator::Identifier var2 = "var2";
			const CCalculator::Value value2 = 45;
			calculator.AssignVariable(var1, value1);
			calculator.AssignVariable(var2, value2);

			const CCalculator::Identifier function = "function";
			const CCalculator::Expression expression = {
				.operation = CCalculator::Operation::MULTIPLICATION,
				.arguments = { var1, var2 },
			};
			calculator.CreateFunction(function, expression);

			REQUIRE(ApproximatelyEquals(
				calculator.GetIdentifierValue(function),
				value1 * value2));
		}

		SECTION("overflowing function results in an error")
		{
			const CCalculator::Identifier var1 = "var1";
			const CCalculator::Value value1 = std::numeric_limits<CCalculator::Value>::max();
			const CCalculator::Identifier var2 = "var2";
			const CCalculator::Value value2 = 10;
			calculator.AssignVariable(var1, value1);
			calculator.AssignVariable(var2, value2);

			const CCalculator::Identifier function = "function";
			const CCalculator::Expression expression = {
				.operation = CCalculator::Operation::MULTIPLICATION,
				.arguments = { var1, var2 },
			};
			calculator.CreateFunction(function, expression);

			REQUIRE_THROWS_AS(
				calculator.GetIdentifierValue(function),
				std::out_of_range);
		}
	}
}

TEST_CASE("calculator control works correctly")
{
	CCalculator calculator;
	std::istringstream input;
	std::ostringstream output;
	CCalculatorControl control(input, output, calculator);

	SECTION("printing help works correctly")
	{
		input.str("help\nexit\n");
		const std::string result = "$ help                                                     show this message\n"
								   "exit                                                     stop the program\n"
								   "var [identifier]                                         create new variable\n"
								   "let [identifier] = [number]                              assign number value to a variable\n"
								   "let [identifier] = [identifier2]                         assign another variable to a variable\n"
								   "fn [identifier] = [identifier2]                          create simple function\n"
								   "fn [identifier] = [identifier2] [operator] [identifier3] create complex function\n"
								   "print [identifier]                                       print the value of the identifier\n"
								   "printvars                                                print all variables values\n"
								   "printfns                                                 print all functions values\n"
								   "$ Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
	}

	SECTION("variable creation works correctly")
	{
		input.str("var a\nexit\n");
		control.StartControl();
		auto const& variables = calculator.DumpVariables();
		REQUIRE(variables.size() == 1);
		REQUIRE(std::isnan(variables.at("a")));
	}

	SECTION("variable assignment works correctly")
	{
		SECTION("usual assignment works correctly")
		{
			input.str("let a=3\nexit\n");
			control.StartControl();
			auto const& variables = calculator.DumpVariables();
			REQUIRE(variables.size() == 1);
			REQUIRE(variables.at("a") == 3);
		}

		SECTION("overflowing value results in an error")
		{
			input.str(
				"let a = 1" + std::to_string(std::numeric_limits<CCalculator::Value>::max()) + "\nexit\n");
			control.StartControl();
			auto const& variables = calculator.DumpVariables();
			REQUIRE(variables.empty());
		}

		SECTION("recursive assignment results in an error")
		{
			input.str("let a = a\nexit\n");
			control.StartControl();
			auto const& variables = calculator.DumpVariables();
			REQUIRE(variables.empty());
		}
	}

	SECTION("function creation works correctly")
	{
		input.str("let a=3\nfn f=a\nexit\n");
		control.StartControl();
		auto const functions = calculator.DumpFunctions();
		REQUIRE(functions.size() == 1);
		REQUIRE(functions.at("f") == 3);
	}

	SECTION("identifier printing works correctly")
	{
		input.str(
			"var a\nlet b = 3\nfn f = b\n"
			"print a\nprint b\nprint f\n"
			"exit\n");
		const std::string result = "$ $ $ $ nan\n"
								   "$ 3.00\n"
								   "$ 3.00\n"
								   "$ Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
	}

	SECTION("printing all variables works correctly")
	{
		input.str(
			"var a\nlet b = a\nlet c=42\n"
			"printvars\n"
			"exit\n");
		const std::string result = "$ $ $ "
								   "$ a:nan\nb:nan\nc:42.00\n"
								   "$ Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
	}

	SECTION("printing all function works correctly")
	{
		input.str(
			"var a\nlet b=3\nfn c = a\nfn d = b\nfn e = d + b\n"
			"printfns\n"
			"exit\n");
		const std::string result = "$ $ $ $ $ "
								   "$ c:nan\nd:3.00\ne:6.00\n"
								   "$ Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
	}

	SECTION("unknown expression results in an error")
	{
		input.str("what's up dog\nexit\n");
		const std::string result = "$ Error: invalid expression\n$ Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
	}
}
