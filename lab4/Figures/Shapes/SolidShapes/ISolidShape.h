#pragma once

#include "../IShape.h"

class ISolidShape // TODO: inherit from IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;
};
