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

	friend const CRational operator+(const CRational& r1, const CRational& r2);
	friend const CRational operator-(const CRational& r1, const CRational& r2);

	CRational& operator+=(const CRational& other);
	CRational& operator-=(const CRational& other);

	friend const CRational operator*(const CRational& r1, const CRational& r2);
	friend const CRational operator/(const CRational& r1, const CRational& r2);

	CRational& operator*=(const CRational& other);
	CRational& operator/=(const CRational& other);

	friend bool operator==(const CRational& r1, const CRational& r2);
	friend bool operator!=(const CRational& r1, const CRational& r2);

	friend bool operator<(const CRational& r1, const CRational& r2);
	friend bool operator<=(const CRational& r1, const CRational& r2);
	friend bool operator>(const CRational& r1, const CRational& r2);
	friend bool operator>=(const CRational& r1, const CRational& r2);

	friend std::ostream& operator<<(std::ostream& stream, const CRational& r);
	friend std::istream& operator>>(std::istream& stream, CRational& r);

private:
	void Normalize();

	int m_numerator = 0;
	int m_denominator = 1;
};
