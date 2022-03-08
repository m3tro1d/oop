#define CATCH_CONFIG_MAIN
#include "../CCalculator.h"
#include "catch.hpp"

TEST_CASE("base calculator works correctly")
{
	CCalculator calculator;

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
