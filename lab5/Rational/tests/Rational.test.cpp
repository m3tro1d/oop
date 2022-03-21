#define CATCH_CONFIG_MAIN
#include "../CRational.h"
#include "catch.hpp"

SCENARIO("creating a rational number")
{
	GIVEN("nothing")
	{
		CRational r;

		THEN("numerator is 0")
		{
			REQUIRE(r.GetNumerator() == 0);
		}

		THEN("denominator is 1")
		{
			REQUIRE(r.GetDenominator() == 1);
		}
	}

	GIVEN("a number")
	{
		int number = 42;
		CRational r = number;

		THEN("numerator equals to that number")
		{
			REQUIRE(r.GetNumerator() == number);
		}

		THEN("denominator is 1")
		{
			REQUIRE(r.GetDenominator() == 1);
		}
	}

	GIVEN("numerator and denominator")
	{
		int numerator = 42;
		int denominator = 69;
		CRational r(numerator, denominator);

		THEN("numerator is the same")
		{
			REQUIRE(r.GetNumerator() == numerator);
		}

		THEN("denominator is the same")
		{
			REQUIRE(r.GetDenominator() == denominator);
		}
	}
}

SCENARIO("getting double representation of a rational number")
{
	// TODO
}
