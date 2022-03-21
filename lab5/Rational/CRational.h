#pragma once

#include <iostream>

class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	int GetNumerator() const;
	int GetDenominator() const;

	double ToDouble() const;

	CRational operator+() const;
	CRational operator-() const;

	// TODO

private:
	int m_numerator;
	int m_denominator;
};
