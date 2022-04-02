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
		SECTION("no normalization")
		{
			int numerator = 13;
			int denominator = 69;
			CRational r(numerator, denominator);

			REQUIRE(r.GetNumerator() == numerator);
			REQUIRE(r.GetDenominator() == denominator);
		}

		SECTION("with normalization")
		{
			int numerator = 100;
			int denominator = 12;
			CRational r(numerator, denominator);

			REQUIRE(r.GetNumerator() == 25);
			REQUIRE(r.GetDenominator() == 3);
		}

		SECTION("with negative numerator normalization")
		{
			int numerator = -112;
			int denominator = 6;
			CRational r(numerator, denominator);

			REQUIRE(r.GetNumerator() == -56);
			REQUIRE(r.GetDenominator() == 3);
		}
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

TEST_CASE("getting compound fraction with a rational number")
{
	SECTION("full division")
	{
		// TODO
	}

	SECTION("without remainder normalization")
	{
		// TODO
	}

	SECTION("with remainder normalization")
	{
		// TODO
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

			REQUIRE(result.GetNumerator() == 199);
			REQUIRE(result.GetDenominator() == 63);
		}

		SECTION("with normalization")
		{
			CRational r1(49, 100);
			CRational r2(1, 100);
			auto const result = r1 + r2;

			REQUIRE(result.GetNumerator() == 1);
			REQUIRE(result.GetDenominator() == 2);
		}
	}

	SECTION("rational + number")
	{
		SECTION("no normalization")
		{
			CRational r1(12, 7);
			int n = 2;
			auto const result = r1 + n;

			REQUIRE(result.GetNumerator() == 26);
			REQUIRE(result.GetDenominator() == 7);
		}

		SECTION("with normalization")
		{
			CRational r1(14, 7);
			int n = 3;
			auto const result = r1 + n;

			REQUIRE(result.GetNumerator() == 5);
			REQUIRE(result.GetDenominator() == 1);
		}
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

TEST_CASE("rational numbers summation-assignment")
{
	SECTION("+= rational")
	{
		// TODO
	}

	SECTION("+= number")
	{
		// TODO
	}
}

TEST_CASE("rational numbers subtraction-assignment")
{
	SECTION("-= rational")
	{
		// TODO
	}

	SECTION("-= number")
	{
		// TODO
	}
}

TEST_CASE("rational numbers multiplication")
{
	SECTION("rational * rational")
	{
		// TODO
	}

	SECTION("rational * number")
	{
		// TODO
	}
}

TEST_CASE("rational numbers division")
{
	SECTION("rational / rational")
	{
		// TODO
	}

	SECTION("rational / number")
	{
		// TODO
	}
}

TEST_CASE("rational numbers multiplication-assignment")
{
	SECTION("*= rational")
	{
		// TODO
	}

	SECTION("*= number")
	{
		// TODO
	}
}

TEST_CASE("rational numbers division-assignment")
{
	SECTION("/= rational")
	{
		// TODO
	}

	SECTION("/= number")
	{
		// TODO
	}
}

TEST_CASE("rational numbers comparison")
{
	SECTION("equality")
	{
		SECTION("== rational")
		{
			// TODO
		}

		SECTION("== number")
		{
			// TODO
		}
	}

	SECTION("inequality")
	{
		SECTION("!= rational")
		{
			// TODO
		}

		SECTION("!= number")
		{
			// TODO
		}
	}
}

TEST_CASE("rational numbers greater-less relation")
{
	SECTION("less than")
	{
		SECTION("rational < rational")
		{
			// TODO
		}

		SECTION("rational < number")
		{
			// TODO
		}

		SECTION("number < rational")
		{
			// TODO
		}
	}

	SECTION("less or equal to")
	{
		SECTION("rational <= rational")
		{
			// TODO
		}

		SECTION("rational <= number")
		{
			// TODO
		}

		SECTION("number <= rational")
		{
			// TODO
		}
	}

	SECTION("more than")
	{
		SECTION("rational > rational")
		{
			// TODO
		}

		SECTION("rational > number")
		{
			// TODO
		}

		SECTION("number > rational")
		{
			// TODO
		}
	}

	SECTION("more or equal to")
	{
		SECTION("rational >= rational")
		{
			// TODO
		}

		SECTION("rational >= number")
		{
			// TODO
		}

		SECTION("number >= rational")
		{
			// TODO
		}
	}
}

TEST_CASE("writing rational number in the stream")
{
	// TODO
	REQUIRE(true);
}

TEST_CASE("reading rational number from the stream")
{
	// TODO
	REQUIRE(true);
}
