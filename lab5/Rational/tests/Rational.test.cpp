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
		CRational r(14, 2);
		auto const result = r.ToCompoundFraction();

		REQUIRE(result.first == 7);
		REQUIRE(result.second.GetNumerator() == 0);
		REQUIRE(result.second.GetDenominator() == 1);
	}

	SECTION("without remainder normalization")
	{
		CRational r(15, 2);
		auto const result = r.ToCompoundFraction();

		REQUIRE(result.first == 7);
		REQUIRE(result.second.GetNumerator() == 1);
		REQUIRE(result.second.GetDenominator() == 2);
	}

	SECTION("with remainder normalization")
	{
		CRational r(16, 6);
		auto const result = r.ToCompoundFraction();

		REQUIRE(result.first == 2);
		REQUIRE(result.second.GetNumerator() == 2);
		REQUIRE(result.second.GetDenominator() == 3);
	}

	SECTION("negative rational")
	{
		CRational r(-9, 4);
		auto const result = r.ToCompoundFraction();

		REQUIRE(result.first == -2);
		REQUIRE(result.second.GetNumerator() == -1);
		REQUIRE(result.second.GetDenominator() == 4);
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
			auto const result = n + r1;

			REQUIRE(result.GetNumerator() == 5);
			REQUIRE(result.GetDenominator() == 1);
		}
	}
}

TEST_CASE("rational numbers subtraction")
{
	SECTION("rational - rational")
	{
		SECTION("no normalization")
		{
			CRational r1(12, 7);
			CRational r2(13, 9);
			auto const result = r1 - r2;

			REQUIRE(result.GetNumerator() == 17);
			REQUIRE(result.GetDenominator() == 63);
		}

		SECTION("with normalization")
		{
			CRational r1(51, 100);
			CRational r2(1, 100);
			auto const result = r1 - r2;

			REQUIRE(result.GetNumerator() == 1);
			REQUIRE(result.GetDenominator() == 2);
		}
	}

	SECTION("rational - number")
	{
		SECTION("no normalization")
		{
			CRational r1(12, 7);
			int n = 2;
			auto const result = r1 - n;

			REQUIRE(result.GetNumerator() == -2);
			REQUIRE(result.GetDenominator() == 7);
		}

		SECTION("with normalization")
		{
			CRational r1(14, 7);
			int n = 3;
			auto const result = n - r1;

			REQUIRE(result.GetNumerator() == 1);
			REQUIRE(result.GetDenominator() == 1);
		}
	}
}

TEST_CASE("rational numbers summation-assignment")
{
	SECTION("+= rational")
	{
		SECTION("no normalization")
		{
			CRational r1(12, 7);
			CRational r2(13, 9);
			r1 += r2;

			REQUIRE(r1.GetNumerator() == 199);
			REQUIRE(r1.GetDenominator() == 63);
		}

		SECTION("with normalization")
		{
			CRational r1(49, 100);
			CRational r2(1, 100);
			r1 += r2;

			REQUIRE(r1.GetNumerator() == 1);
			REQUIRE(r1.GetDenominator() == 2);
		}
	}

	SECTION("+= number")
	{
		SECTION("no normalization")
		{
			CRational r1(12, 7);
			int n = 2;
			r1 += n;

			REQUIRE(r1.GetNumerator() == 26);
			REQUIRE(r1.GetDenominator() == 7);
		}

		SECTION("with normalization")
		{
			CRational r1(14, 7);
			int n = 3;
			r1 += n;

			REQUIRE(r1.GetNumerator() == 5);
			REQUIRE(r1.GetDenominator() == 1);
		}
	}

	SECTION("returns reference")
	{
		CRational r(2, 3);
		(r += 2) += 3;

		REQUIRE(r.GetNumerator() == 17);
		REQUIRE(r.GetDenominator() == 3);
	}
}

TEST_CASE("rational numbers subtraction-assignment")
{
	SECTION("-= rational")
	{
		SECTION("no normalization")
		{
			CRational r1(12, 7);
			CRational r2(13, 9);
			r1 -= r2;

			REQUIRE(r1.GetNumerator() == 17);
			REQUIRE(r1.GetDenominator() == 63);
		}

		SECTION("with normalization")
		{
			CRational r1(51, 100);
			CRational r2(1, 100);
			r1 -= r2;

			REQUIRE(r1.GetNumerator() == 1);
			REQUIRE(r1.GetDenominator() == 2);
		}
	}

	SECTION("-= number")
	{
		SECTION("no normalization")
		{
			CRational r1(12, 7);
			int n = 2;
			r1 -= n;

			REQUIRE(r1.GetNumerator() == -2);
			REQUIRE(r1.GetDenominator() == 7);
		}

		SECTION("with normalization")
		{
			CRational r1(14, 7);
			int n = 3;
			r1 -= n;

			REQUIRE(r1.GetNumerator() == -1);
			REQUIRE(r1.GetDenominator() == 1);
		}
	}

	SECTION("returns reference")
	{
		CRational r(2, 3);
		(r -= 2) -= 3;

		REQUIRE(r.GetNumerator() == -13);
		REQUIRE(r.GetDenominator() == 3);
	}
}

TEST_CASE("rational numbers multiplication")
{
	SECTION("rational * rational")
	{
		SECTION("no normalization")
		{
			CRational r1(2, 3);
			CRational r2(13, 7);
			auto const result = r1 * r2;

			REQUIRE(result.GetNumerator() == 26);
			REQUIRE(result.GetDenominator() == 21);
		}

		SECTION("with normalization")
		{
			CRational r1(2, 3);
			CRational r2(12, 7);
			auto const result = r1 * r2;

			REQUIRE(result.GetNumerator() == 8);
			REQUIRE(result.GetDenominator() == 7);
		}
	}

	SECTION("rational * number")
	{
		SECTION("no normalization")
		{
			CRational r(2, 3);
			int n = 13;
			auto const result = r * n;

			REQUIRE(result.GetNumerator() == 26);
			REQUIRE(result.GetDenominator() == 3);
		}

		SECTION("with normalization")
		{
			CRational r(14, 7);
			int n = 12;
			auto const result = n * r;

			REQUIRE(result.GetNumerator() == 24);
			REQUIRE(result.GetDenominator() == 1);
		}
	}
}

TEST_CASE("rational numbers division")
{
	SECTION("rational / rational")
	{
		SECTION("no normalization")
		{
			CRational r1(2, 3);
			CRational r2(13, 4);
			auto const result = r1 / r2;

			REQUIRE(result.GetNumerator() == 8);
			REQUIRE(result.GetDenominator() == 39);
		}

		SECTION("with normalization")
		{
			CRational r1(2, 3);
			CRational r2(13, 4);
			auto const result = r1 / r2;

			REQUIRE(result.GetNumerator() == 8);
			REQUIRE(result.GetDenominator() == 39);
		}
	}

	SECTION("rational / number")
	{
		SECTION("no normalization")
		{
			CRational r(13, 69);
			int n = 3;
			auto const result = r / n;

			REQUIRE(result.GetNumerator() == 13);
			REQUIRE(result.GetDenominator() == 207);
		}

		SECTION("with normalization")
		{
			CRational r(15, 70);
			int n = 3;
			auto const result = n / r;

			REQUIRE(result.GetNumerator() == 14);
			REQUIRE(result.GetDenominator() == 1);
		}
	}

	SECTION("division by zero throws exception")
	{
		CRational r(2, 3);

		REQUIRE_THROWS_AS(r / 0, std::invalid_argument);
		REQUIRE_THROWS_AS(r / CRational(), std::invalid_argument);
	}
}

TEST_CASE("rational numbers multiplication-assignment")
{
	SECTION("*= rational")
	{
		SECTION("no normalization")
		{
			CRational r1(2, 3);
			CRational r2(13, 7);
			r1 *= r2;

			REQUIRE(r1.GetNumerator() == 26);
			REQUIRE(r1.GetDenominator() == 21);
		}

		SECTION("with normalization")
		{
			CRational r1(2, 3);
			CRational r2(12, 7);
			r1 *= r2;

			REQUIRE(r1.GetNumerator() == 8);
			REQUIRE(r1.GetDenominator() == 7);
		}
	}

	SECTION("*= number")
	{
		SECTION("no normalization")
		{
			CRational r(2, 3);
			int n = 13;
			r *= n;

			REQUIRE(r.GetNumerator() == 26);
			REQUIRE(r.GetDenominator() == 3);
		}

		SECTION("with normalization")
		{
			CRational r(14, 7);
			int n = 12;
			r *= n;

			REQUIRE(r.GetNumerator() == 24);
			REQUIRE(r.GetDenominator() == 1);
		}
	}

	SECTION("returns reference")
	{
		CRational r(2, 3);
		(r *= 2) *= 3;

		REQUIRE(r.GetNumerator() == 4);
		REQUIRE(r.GetDenominator() == 1);
	}
}

TEST_CASE("rational numbers division-assignment")
{
	SECTION("/= rational")
	{
		SECTION("no normalization")
		{
			CRational r1(2, 3);
			CRational r2(13, 4);
			r1 /= r2;

			REQUIRE(r1.GetNumerator() == 8);
			REQUIRE(r1.GetDenominator() == 39);
		}

		SECTION("with normalization")
		{
			CRational r1(2, 3);
			CRational r2(13, 4);
			r1 /= r2;

			REQUIRE(r1.GetNumerator() == 8);
			REQUIRE(r1.GetDenominator() == 39);
		}
	}

	SECTION("rational / number")
	{
		SECTION("no normalization")
		{
			CRational r(13, 69);
			int n = 3;
			r /= n;

			REQUIRE(r.GetNumerator() == 13);
			REQUIRE(r.GetDenominator() == 207);
		}

		SECTION("with normalization")
		{
			CRational r(15, 70);
			int n = 3;
			r /= n;

			REQUIRE(r.GetNumerator() == 1);
			REQUIRE(r.GetDenominator() == 14);
		}
	}

	SECTION("division by zero throws exception")
	{
		CRational r(2, 3);

		REQUIRE_THROWS_AS(r /= 0, std::invalid_argument);
		REQUIRE_THROWS_AS(r /= CRational(), std::invalid_argument);
	}

	SECTION("returns reference")
	{
		CRational r(2, 3);
		(r /= 2) /= 3;

		REQUIRE(r.GetNumerator() == 1);
		REQUIRE(r.GetDenominator() == 9);
	}
}

TEST_CASE("rational numbers comparison")
{
	SECTION("equality")
	{
		SECTION("== rational")
		{
			CRational r1(2, 3);
			CRational r2(2, 5);

			REQUIRE(r1 == r1);
			REQUIRE_FALSE(r1 == r2);
		}

		SECTION("== number")
		{
			CRational r1 = 4;
			CRational r2(2, 3);

			REQUIRE(r1 == 4);
			REQUIRE_FALSE(r2 == 4);
		}
	}

	SECTION("inequality")
	{
		SECTION("!= rational")
		{
			CRational r1(2, 3);
			CRational r2(2, 5);

			REQUIRE_FALSE(r1 != r1);
			REQUIRE(r1 != r2);
		}

		SECTION("!= number")
		{
			CRational r1 = 4;
			CRational r2(2, 3);

			REQUIRE_FALSE(r1 != 4);
			REQUIRE(r2 != 4);
		}
	}
}

TEST_CASE("rational numbers greater-less relation")
{
	SECTION("less than")
	{
		SECTION("rational < rational")
		{
			REQUIRE(CRational(1, 5) < CRational(2, 3));
			REQUIRE_FALSE(CRational(12, 3) < CRational(1, 3));
			REQUIRE_FALSE(CRational(2, 3) < CRational(2, 3));
		}

		SECTION("rational < number")
		{
			REQUIRE(CRational(1, 2) < 7);
			REQUIRE_FALSE(CRational(7, 6) < 1);
			REQUIRE_FALSE(CRational(4) < 4);
		}

		SECTION("number < rational")
		{
			REQUIRE(3 < CRational(7, 2));
			REQUIRE_FALSE(2 < CRational(7, 6));
			REQUIRE_FALSE(4 < CRational(4));
		}
	}

	SECTION("less or equal to")
	{
		SECTION("rational <= rational")
		{
			REQUIRE(CRational(1, 5) <= CRational(2, 3));
			REQUIRE_FALSE(CRational(12, 3) <= CRational(1, 3));
			REQUIRE(CRational(2, 3) <= CRational(2, 3));
		}

		SECTION("rational <= number")
		{
			REQUIRE(CRational(1, 2) <= 7);
			REQUIRE_FALSE(CRational(7, 6) <= 1);
			REQUIRE(CRational(4) <= 4);
		}

		SECTION("number <= rational")
		{
			REQUIRE(3 <= CRational(7, 2));
			REQUIRE_FALSE(2 <= CRational(7, 6));
			REQUIRE(4 <= CRational(4));
		}
	}

	SECTION("more than")
	{
		SECTION("rational > rational")
		{
			REQUIRE(CRational(2, 3) > CRational(1, 5));
			REQUIRE_FALSE(CRational(1, 3) > CRational(12, 13));
			REQUIRE_FALSE(CRational(2, 3) > CRational(2, 3));
		}

		SECTION("rational > number")
		{
			REQUIRE(CRational(7, 2) > 3);
			REQUIRE_FALSE(CRational(7, 6) > 2);
			REQUIRE_FALSE(CRational(4) > 4);
		}

		SECTION("number > rational")
		{
			REQUIRE(7 > CRational(1, 2));
			REQUIRE_FALSE(1 > CRational(7, 6));
			REQUIRE_FALSE(4 > CRational(4));
		}
	}

	SECTION("more or equal to")
	{
		SECTION("rational >= rational")
		{
			REQUIRE(CRational(2, 3) >= CRational(1, 5));
			REQUIRE_FALSE(CRational(1, 3) >= CRational(12, 13));
			REQUIRE(CRational(2, 3) >= CRational(2, 3));
		}

		SECTION("rational >= number")
		{
			REQUIRE(CRational(7, 2) >= 3);
			REQUIRE_FALSE(CRational(7, 6) >= 2);
			REQUIRE(CRational(4) >= 4);
		}

		SECTION("number >= rational")
		{
			REQUIRE(7 >= CRational(1, 2));
			REQUIRE_FALSE(1 >= CRational(7, 6));
			REQUIRE(4 >= CRational(4));
		}
	}
}

TEST_CASE("printing rational number in the stream")
{
	std::stringstream output;

	SECTION("positive")
	{
		CRational r(12, 5);
		output << r;

		REQUIRE(output.str() == "12/5");
	}

	SECTION("negative")
	{
		CRational r(-12, 7);
		output << r;

		REQUIRE(output.str() == "-12/7");
	}

	SECTION("zero")
	{
		CRational r;
		output << r;

		REQUIRE(output.str() == "0/1");
	}

	SECTION("integer number")
	{
		CRational r = 12;
		output << r;

		REQUIRE(output.str() == "12/1");
	}
}

TEST_CASE("reading rational number from the stream")
{
	std::stringstream input;

	SECTION("positive")
	{
		input.str("12/5");
		CRational r;
		input >> r;

		REQUIRE(r.GetNumerator() == 12);
		REQUIRE(r.GetDenominator() == 5);
	}

	SECTION("positive")
	{
		input.str("-12/7");
		CRational r;
		input >> r;

		REQUIRE(r.GetNumerator() == -12);
		REQUIRE(r.GetDenominator() == 7);
	}

	SECTION("zero")
	{
		input.str("0/12");
		CRational r;
		input >> r;

		REQUIRE(r.GetNumerator() == 0);
		REQUIRE(r.GetDenominator() == 1);
	}

	SECTION("integer number")
	{
		input.str("12/1");
		CRational r;
		input >> r;

		REQUIRE(r.GetNumerator() == 12);
		REQUIRE(r.GetDenominator() == 1);
	}

	SECTION("invalid rational sets failbit")
	{
		SECTION("invalid numerator")
		{
			input.str("abc/42");
			CRational r;
			input >> r;

			REQUIRE(input.fail());
		}

		SECTION("invalid denominator")
		{
			input.str("12/abc");
			CRational r;
			input >> r;

			REQUIRE(input.fail());
		}

		SECTION("invalid separator")
		{
			input.str("12?7");
			CRational r;
			input >> r;

			REQUIRE(input.fail());
		}

		SECTION("no numerator")
		{
			input.str("/42");
			CRational r;
			input >> r;

			REQUIRE(input.fail());
		}

		SECTION("no denominator")
		{
			input.str("12/");
			CRational r;
			input >> r;

			REQUIRE(input.fail());
		}

		SECTION("plain number")
		{
			input.str("420");
			CRational r;
			input >> r;

			REQUIRE(input.fail());
		}
	}
}
