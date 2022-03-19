#pragma once

#include "../CShape.h"
#include "ISolidShape.h"

class CSolidShape : public ISolidShape
{
public:
	CSolidShape(uint32_t outlineColor, uint32_t fillColor);

	virtual ~CSolidShape() = default;

	uint32_t GetOutlineColor() const final;
	uint32_t GetFillColor() const final;

protected:
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
