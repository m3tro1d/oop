#pragma once

#include <iostream>
#include <numeric>

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

	friend CRational operator+(const CRational& r1, const CRational& r2);
	friend CRational operator+(const CRational& r1, const int& n);
	friend CRational operator+(const int& n, const CRational& r2);

	friend CRational operator-(const CRational& r1, const CRational& r2);
	friend CRational operator-(const CRational& r1, const int& n);
	friend CRational operator-(const int& n, const CRational& r2);

	CRational& operator+=(const CRational& other);
	CRational& operator+=(const int& n);

	CRational& operator-=(const CRational& other);
	CRational& operator-=(const int& n);

private:
	void Normalize();

	int m_numerator;
	int m_denominator;
};
