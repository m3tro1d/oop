#pragma once

#include "IShape.h"

class CShape : public IShape
{
public:
	CShape(uint32_t outlineColor);

	uint32_t GetOutlineColor() const final;

protected:
	uint32_t m_outlineColor;
};
