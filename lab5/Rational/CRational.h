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

	std::pair<int, CRational> ToCompoundFraction() const;

	const CRational operator+() const;
	const CRational operator-() const;

	const CRational operator+(const CRational& other) const;
	const CRational operator-(const CRational& other) const;

	CRational& operator+=(const CRational& other);
	CRational& operator-=(const CRational& other);

	const CRational operator*(const CRational& other) const;
	const CRational operator/(const CRational& other) const;

	CRational& operator*=(const CRational& other);
	CRational& operator/=(const CRational& other);

	bool operator==(const CRational& other) const;
	bool operator!=(const CRational& other) const;

	bool operator<(const CRational& other) const;
	bool operator<=(const CRational& other) const;
	bool operator>(const CRational& other) const;
	bool operator>=(const CRational& other) const;

	friend std::ostream& operator<<(std::ostream& stream, const CRational& r);
	friend std::istream& operator>>(std::istream& stream, CRational& r);

private:
	void Normalize();

	int m_numerator;
	int m_denominator;
};
