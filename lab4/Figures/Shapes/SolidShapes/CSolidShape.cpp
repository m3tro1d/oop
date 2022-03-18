#include "CSolidShape.h"

CSolidShape::CSolidShape(uint32_t outlineColor, uint32_t fillColor)
	: CShape(outlineColor)
	, m_fillColor(fillColor)
{
}

uint32_t CSolidShape::GetFillColor() const
{
	return m_fillColor;
}
