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

	// FIND_OUT: implicit constructor call adding rational and number
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

	friend CRational operator*(const CRational& r1, const CRational& r2);
	friend CRational operator*(const CRational& r1, const int& n);
	friend CRational operator*(const int& n, const CRational& r2);

	friend CRational operator/(const CRational& r1, const CRational& r2);
	friend CRational operator/(const CRational& r1, const int& n);
	friend CRational operator/(const int& n, const CRational& r2);

	CRational& operator*=(const CRational& other);
	CRational& operator*=(const int& n);

	CRational& operator/=(const CRational& other);
	CRational& operator/=(const int& n);

	friend bool operator==(const CRational& r1, const CRational& r2);
	friend bool operator==(const CRational& r1, const int& n);
	friend bool operator==(const int& n, const CRational& r2);

	friend bool operator!=(const CRational& r1, const CRational& r2);
	friend bool operator!=(const CRational& r1, const int& n);
	friend bool operator!=(const int& n, const CRational& r2);

	// TODO: < <= > >=

	friend std::ostream& operator<<(std::ostream& stream, const CRational& r);
	friend std::istream& operator>>(std::istream& stream, CRational& r);

private:
	void Normalize();

	int m_numerator;
	int m_denominator;
};
