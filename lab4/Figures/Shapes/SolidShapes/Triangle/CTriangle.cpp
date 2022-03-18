#include "CTriangle.h"

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetArea() const
{
	auto val1 = m_vertex1.GetY() * (m_vertex2.GetY() - m_vertex3.GetY());
	auto val2 = m_vertex2.GetX() * (m_vertex3.GetY() - m_vertex1.GetY());
	auto val3 = m_vertex3.GetX() * (m_vertex1.GetY() - m_vertex2.GetY());

	return std::abs(val1 + val2 + val3);
}

double CTriangle::GetPerimeter() const
{
	auto distance12 = CPoint::Distance(m_vertex1, m_vertex2);
	auto distance23 = CPoint::Distance(m_vertex2, m_vertex3);
	auto distance31 = CPoint::Distance(m_vertex3, m_vertex1);

	return distance12 + distance23 + distance31;
}

std::string CTriangle::ToString() const
{
	std::stringstream result;
	result << std::fixed << std::setprecision(2)
		   << "TRIANGLE\n"
		   << "  (" << m_vertex1.GetX() << ", " << m_vertex1.GetY() << ")\n"
		   << "  (" << m_vertex2.GetX() << ", " << m_vertex2.GetY() << ")\n"
		   << "  (" << m_vertex3.GetX() << ", " << m_vertex3.GetY() << ")\n"
		   << "  outline: #" << std::hex << m_outlineColor << "\n"
		   << "  fill: #" << std::hex << m_fillColor << "\n";

	return result.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
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
