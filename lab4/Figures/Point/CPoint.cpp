#include "CPoint.h"

CPoint::CPoint(double x, double y)
	: m_x(x)
	, m_y(y)
{
}

double CPoint::GetX() const
{
	return m_x;
}

double CPoint::GetY() const
{
	return m_y;
}

double CPoint::Distance(const CPoint& p1, const CPoint& p2)
{
	auto xSquared = (p2.GetX() - p1.GetX()) * (p2.GetX() - p1.GetX());
	auto ySquared = (p2.GetY() - p1.GetY()) * (p2.GetY() - p1.GetY());

	return std::sqrt(xSquared + ySquared);
}
