#pragma once

#include "./ITaxi.h"
#include "CCarImpl.h"
#include <vector>

class CTaxi : public CCarImpl<ITaxi>
{
public:
	CTaxi(std::size_t placeCount, MakeOfTheCar makeOfTheCar);
};
