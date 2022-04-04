#pragma once

#include <iostream>
#include <numeric>

class CRational
{
public:
	CRational() = default;
	CRational(int value);
	CRational(int numerator, int denominator);

	int GetNumerator() const;
	int GetDenominator() const;

	double ToDouble() const;

	std::pair<int, CRational> ToCompoundFraction() const;

	CRational const operator+() const;
	CRational const operator-() const;

	CRational& operator+=(CRational const& other);
	CRational& operator-=(CRational const& other);

	CRational& operator*=(CRational const& other);
	CRational& operator/=(CRational const& other);

private:
	void Normalize();

	int m_numerator = 0;
	int m_denominator = 1;
};

CRational const operator+(CRational r1, CRational const& r2);
CRational const operator-(CRational r1, CRational const& r2);

CRational const operator*(CRational r1, CRational const& r2);
CRational const operator/(CRational r1, CRational const& r2);

bool operator==(CRational const& r1, CRational const& r2);
bool operator!=(CRational const& r1, CRational const& r2);

bool operator<(CRational const& r1, CRational const& r2);
bool operator<=(CRational const& r1, CRational const& r2);
bool operator>(CRational const& r1, CRational const& r2);
bool operator>=(CRational const& r1, CRational const& r2);

std::ostream& operator<<(std::ostream& stream, CRational const& r);
std::istream& operator>>(std::istream& stream, CRational& r);
