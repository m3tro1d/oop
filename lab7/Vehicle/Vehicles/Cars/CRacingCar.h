#pragma once

#include "./IRacingCar.h"
#include "CCarImpl.h"
#include <vector>

class CRacingCar : public CCarImpl<IRacingCar>
{
public:
	CRacingCar(std::size_t placeCount, MakeOfTheCar makeOfTheCar);
};
