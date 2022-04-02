#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-const-return-type"
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

const CRational CRational::operator+(const CRational& other) const
{
	int commonDenominator = std::lcm(m_denominator, other.m_denominator);
	int numerator = m_numerator * (commonDenominator / m_denominator);
	int otherNumerator = other.m_numerator * (commonDenominator / other.m_denominator);

	return { numerator + otherNumerator, commonDenominator };
}

const CRational CRational::operator-(const CRational& other) const
{
	return *this + (-other);
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

const CRational CRational::operator*(const CRational& other) const
{
	int commonDenominator = std::lcm(m_denominator, other.m_denominator);
	int numerator = m_numerator * (commonDenominator / m_denominator);
	int otherNumerator = other.m_numerator * (commonDenominator / other.m_denominator);

	return { numerator * otherNumerator, commonDenominator };
}

const CRational CRational::operator/(const CRational& other) const
{
	if (other.m_numerator == 0)
	{
		throw std::invalid_argument("zero division");
	}

	return *this * CRational(other.m_denominator, other.m_numerator);
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

bool CRational::operator==(const CRational& other) const
{
	return (m_numerator == other.m_numerator) && (m_denominator == other.m_denominator);
}

bool CRational::operator!=(const CRational& other) const
{
	return !(*this == other);
}

bool CRational::operator<(const CRational& other) const
{
	int commonDenominator = std::lcm(m_denominator, other.m_denominator);
	int numerator = m_numerator * (commonDenominator / m_denominator);
	int otherNumerator = other.m_numerator * (commonDenominator / other.m_denominator);

	return numerator < otherNumerator;
}

bool CRational::operator<=(const CRational& other) const
{
	return (*this < other) || (*this == other);
}

bool CRational::operator>(const CRational& other) const
{
	return !(*this <= other);
}

bool CRational::operator>=(const CRational& other) const
{
	return !(*this < other);
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

#pragma clang diagnostic pop
