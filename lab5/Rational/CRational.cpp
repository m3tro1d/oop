#include "CRational.h"

constexpr char DIVIDER = '/';

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	if (m_denominator == 0)
	{
		throw std::logic_error("zero division");
	}

	return m_numerator / static_cast<double>(m_denominator);
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integerPart = m_numerator / m_denominator;
	int newNumerator = m_numerator % m_denominator;

	return { integerPart, { newNumerator, m_denominator } };
}

const CRational CRational::operator+() const
{
	return *this;
}

const CRational CRational::operator-() const
{
	return { -m_numerator, m_denominator };
}

const CRational operator+(const CRational& r1, const CRational& r2)
{
	int commonDenominator = std::lcm(r1.m_denominator, r2.m_denominator);
	int numerator1 = r1.m_numerator * (commonDenominator / r1.m_denominator);
	int numerator2 = r2.m_numerator * (commonDenominator / r2.m_denominator);

	return { numerator1 + numerator2, commonDenominator };
}

const CRational operator-(const CRational& r1, const CRational& r2)
{
	return r1 + (-r2);
}

CRational& CRational::operator+=(const CRational& other)
{
	*this = *this + other;
	return *this;
}

CRational& CRational::operator-=(const CRational& other)
{
	*this = *this - other;
	return *this;
}

const CRational operator*(const CRational& r1, const CRational& r2)
{
	int commonDenominator = std::lcm(r1.m_denominator, r2.m_denominator);
	int numerator1 = r1.m_numerator * (commonDenominator / r1.m_denominator);
	int numerator2 = r2.m_numerator * (commonDenominator / r2.m_denominator);

	return { numerator1 * numerator2, commonDenominator };
}

const CRational operator/(const CRational& r1, const CRational& r2)
{
	if (r2.m_numerator == 0)
	{
		throw std::invalid_argument("zero division");
	}

	return r1 * CRational(r2.m_denominator, r2.m_numerator);
}

CRational& CRational::operator*=(const CRational& other)
{
	*this = *this * other;
	return *this;
}

CRational& CRational::operator/=(const CRational& other)
{
	*this = *this / other;
	return *this;
}

bool operator==(const CRational& r1, const CRational& r2)
{
	return (r1.m_numerator == r2.m_numerator) && (r1.m_denominator == r2.m_denominator);
}

bool operator!=(const CRational& r1, const CRational& r2)
{
	return !(r1 == r2);
}

bool operator<(const CRational& r1, const CRational& r2)
{
	int commonDenominator = std::lcm(r1.m_denominator, r2.m_denominator);
	int numerator1 = r1.m_numerator * (commonDenominator / r1.m_denominator);
	int numerator2 = r2.m_numerator * (commonDenominator / r2.m_denominator);

	return numerator1 < numerator2;
}

bool operator<=(const CRational& r1, const CRational& r2)
{
	return (r1 < r2) || (r1 == r2);
}

bool operator>(const CRational& r1, const CRational& r2)
{
	return !(r1 <= r2);
}

bool operator>=(const CRational& r1, const CRational& r2)
{
	return !(r1 < r2);
}

std::ostream& operator<<(std::ostream& stream, const CRational& r)
{
	stream << r.m_numerator << '/' << r.m_denominator;
	return stream;
}

std::istream& operator>>(std::istream& stream, CRational& r)
{
	int numerator;
	int denominator;
	char divider;

	if (!(stream >> numerator) || !(stream >> divider) || !(stream >> denominator) || divider != DIVIDER)
	{
		stream.setstate(std::ios_base::failbit);
		return stream;
	}

	r = CRational(numerator, denominator);
	return stream;
}

void CRational::Normalize()
{
	int gcd = std::gcd(m_numerator, m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}
