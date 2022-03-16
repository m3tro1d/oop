#pragma once

#include <cmath>

class CPoint
{
public:
	CPoint(double x, double y);

	double GetX() const;
	double GetY() const;

	static double Distance(const CPoint& p1, const CPoint& p2);

private:
	double m_x;
	double m_y;
};
