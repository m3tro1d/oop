#pragma once

#include "IShape.h"

class CShape : public virtual IShape // FIXME: BS solution
{
public:
	CShape(uint32_t outlineColor);

	virtual ~CShape() = default;

	uint32_t GetOutlineColor() const final;

protected:
	uint32_t m_outlineColor;
};
