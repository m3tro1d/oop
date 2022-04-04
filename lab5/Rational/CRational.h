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

	const CRational operator+() const;
	const CRational operator-() const;

	CRational& operator+=(const CRational& other);
	CRational& operator-=(const CRational& other);

	CRational& operator*=(const CRational& other);
	CRational& operator/=(const CRational& other);

private:
	void Normalize();

	int m_numerator = 0;
	int m_denominator = 1;
};

const CRational operator+(const CRational& r1, const CRational& r2);
const CRational operator-(const CRational& r1, const CRational& r2);

const CRational operator*(const CRational& r1, const CRational& r2);
const CRational operator/(const CRational& r1, const CRational& r2);

bool operator==(const CRational& r1, const CRational& r2);
bool operator!=(const CRational& r1, const CRational& r2);

bool operator<(const CRational& r1, const CRational& r2);
bool operator<=(const CRational& r1, const CRational& r2);
bool operator>(const CRational& r1, const CRational& r2);
bool operator>=(const CRational& r1, const CRational& r2);

std::ostream& operator<<(std::ostream& stream, const CRational& r);
std::istream& operator>>(std::istream& stream, CRational& r);
