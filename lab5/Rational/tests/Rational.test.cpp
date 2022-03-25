#define CATCH_CONFIG_MAIN
#include "../CRational.h"
#include "catch.hpp"

bool ApproximatelyEquals(double a, double b)
{
	return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

TEST_CASE("creating a rational number")
{
	SECTION("empty number")
	{
		CRational r;

		REQUIRE(r.GetNumerator() == 0);
		REQUIRE(r.GetDenominator() == 1);
	}

	SECTION("with a single number")
	{
		int number = 42;
		CRational r = number;

		REQUIRE(r.GetNumerator() == number);
		REQUIRE(r.GetDenominator() == 1);
	}

	SECTION("with numerator and denominator")
	{
		int numerator = 42;
		int denominator = 69;
		CRational r(numerator, denominator);

		REQUIRE(r.GetNumerator() == numerator);
		REQUIRE(r.GetDenominator() == denominator);
	}
}

TEST_CASE("getting double representation of a rational number")
{
	SECTION("empty number")
	{
		CRational r;

		REQUIRE(ApproximatelyEquals(r.ToDouble(), 0));
	}

	SECTION("with a single number")
	{
		int number = 42;
		CRational r = number;

		REQUIRE(ApproximatelyEquals(r.ToDouble(), number));
	}

	SECTION("with numerator and denominator")
	{
		int numerator = 42;
		int denominator = 69;
		CRational r(numerator, denominator);

		REQUIRE(ApproximatelyEquals(r.ToDouble(), numerator / static_cast<double>(denominator)));
	}

	SECTION("with zero denominator")
	{
		int numerator = 42;
		int denominator = 0;
		CRational r(numerator, denominator);

		REQUIRE_THROWS_AS(r.ToDouble(), std::logic_error);
	}
}

TEST_CASE("rational numbers summation")
{
	SECTION("rational + rational")
	{
		SECTION("no normalization")
		{
			CRational r1(12, 7);
			CRational r2(13, 9);
			auto const result = r1 + r2;

			REQUIRE(ApproximatelyEquals(result.GetNumerator(), 199));
			REQUIRE(ApproximatelyEquals(result.GetDenominator(), 63));
		}

		SECTION("with normalization")
		{
			// TODO
		}
	}

	SECTION("rational + number")
	{
		// TODO
	}
}

TEST_CASE("rational numbers subtraction")
{
	SECTION("rational - rational")
	{
		// TODO
	}

	SECTION("rational - number")
	{
		// TODO
	}
}
