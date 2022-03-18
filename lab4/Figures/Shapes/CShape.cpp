#include "CShape.h"

CShape::CShape(uint32_t outlineColor)
	: m_outlineColor(outlineColor)
{
}

uint32_t CShape::GetOutlineColor() const
{
	return m_outlineColor;
}
