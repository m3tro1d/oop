#include "CTriangle.h"

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, CSolidShape(outlineColor, fillColor)
{
}

double CTriangle::GetArea() const
{
	double val1 = m_vertex1.GetX() * (m_vertex2.GetY() - m_vertex3.GetY());
	double val2 = m_vertex2.GetX() * (m_vertex3.GetY() - m_vertex1.GetY());
	double val3 = m_vertex3.GetX() * (m_vertex1.GetY() - m_vertex2.GetY());

	return std::abs(val1 + val2 + val3) / 2;
}

double CTriangle::GetPerimeter() const
{
	double a = CPoint::Distance(m_vertex1, m_vertex2);
	double b = CPoint::Distance(m_vertex2, m_vertex3);
	double c = CPoint::Distance(m_vertex3, m_vertex1);

	return a + b + c;
}

std::string CTriangle::ToString() const
{
	std::stringstream result;
	result << std::fixed << std::setprecision(2)
		   << "TRIANGLE\n"
		   << "  vertex1: (" << m_vertex1.GetX() << ", " << m_vertex1.GetY() << ")\n"
		   << "  vertex2: (" << m_vertex2.GetX() << ", " << m_vertex2.GetY() << ")\n"
		   << "  vertex3: (" << m_vertex3.GetX() << ", " << m_vertex3.GetY() << ")\n"
		   << "  outline: ";
	PrintColor(result, GetOutlineColor());
	result << "\n  fill: ";
	PrintColor(result, GetFillColor());
	result << '\n';

	return result.str();
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.DrawPolygon(
		{ m_vertex1,
			m_vertex2,
			m_vertex3 },
		GetOutlineColor(),
		GetFillColor());
}
