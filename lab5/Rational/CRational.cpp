#include "CRational.h"

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
		throw std::logic_error("can not represent as double");
	}

	return m_numerator / static_cast<double>(m_denominator);
}

CRational CRational::operator+() const
{
	return *this;
}

CRational CRational::operator-() const
{
	return { -m_numerator, m_denominator };
}

CRational operator+(const CRational& r1, const CRational& r2)
{
	auto const numerator = r1.m_numerator * r2.m_denominator + r1.m_denominator * r2.m_numerator;
	auto const denominator = r1.m_denominator * r2.m_denominator;
	return { numerator, denominator };
}

CRational operator+(const CRational& r1, const int& n)
{
	return r1 + CRational(n);
}

CRational operator+(const int& n, const CRational& r2)
{
	return r2 + n;
}

CRational operator-(const CRational& r1, const CRational& r2)
{
	return r1 + -r2;
}

CRational operator-(const CRational& r1, const int& n)
{
	return r1 - CRational(n);
}

CRational operator-(const int& n, const CRational& r2)
{
	return CRational(n) - r2;
}

CRational& CRational::operator+=(const CRational& other)
{
	*this = *this + other;
	return *this;
}

CRational& CRational::operator+=(const int& n)
{
	return *this += CRational(n);
}

CRational& CRational::operator-=(const CRational& other)
{
	*this = *this - other;
	return *this;
}

CRational& CRational::operator-=(const int& n)
{
	return *this -= CRational(n);
}