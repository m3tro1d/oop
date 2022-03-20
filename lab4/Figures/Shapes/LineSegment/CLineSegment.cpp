#include "CLineSegment.h"

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, CShape(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return CPoint::Distance(m_startPoint, m_endPoint);
}

std::string CLineSegment::ToString() const
{
	std::stringstream result;
	result << std::fixed << std::setprecision(2)
		   << "LINE SEGMENT\n"
		   << "  start: (" << m_startPoint.GetX() << ", " << m_startPoint.GetY() << ")\n"
		   << "  end: (" << m_endPoint.GetX() << ", " << m_endPoint.GetY() << ")\n"
		   << "  outline: ";
	PrintColor(result, m_outlineColor);
	result << '\n';

	return result.str();
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}
