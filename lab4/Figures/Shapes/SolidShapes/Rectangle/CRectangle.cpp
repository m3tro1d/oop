#include "CRectangle.h"

CRectangle::CRectangle(CPoint leftTop, CPoint rightBottom, uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, CSolidShape(outlineColor, fillColor)
{
}

CRectangle::CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_rightBottom(leftTop.GetX() + width, leftTop.GetY() - height)
	, CSolidShape(outlineColor, fillColor)
{
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

std::string CRectangle::ToString() const
{
	std::stringstream result;
	result << std::fixed << std::setprecision(2) << "RECTANGLE\n"
		   << "  top left: (" << m_leftTop.GetX() << ", " << m_leftTop.GetY() << ")\n"
		   << "  width: " << GetWidth() << "; height: " << GetHeight() << "\n"
		   << "  outline: #" << std::hex << m_outlineColor << "\n"
		   << "  fill: #" << std::hex << m_fillColor << "\n";

	return result.str();
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double CRectangle::GetWidth() const
{
	return m_rightBottom.GetX() - m_leftTop.GetX();
}

double CRectangle::GetHeight() const
{
	return m_leftTop.GetY() - m_rightBottom.GetY();
}
