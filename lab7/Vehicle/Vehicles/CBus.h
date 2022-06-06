#pragma once

#include "./IBus.h"
#include "CVehicleImpl.h"
#include <vector>

class CBus : public CVehicleImpl<IBus>
{
public:
	explicit CBus(std::size_t placeCount);
};
