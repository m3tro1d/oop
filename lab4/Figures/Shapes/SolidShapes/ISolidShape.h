#pragma once

#include "../IShape.h"

class ISolidShape : public virtual IShape // FIXME: BS solution
{
public:
	virtual uint32_t GetFillColor() const = 0;
};
