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
	return CRational(*this);
}

CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}
