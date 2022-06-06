#include "CRacingCar.h"

CRacingCar::CRacingCar(std::size_t placeCount, MakeOfTheCar makeOfTheCar)
	: CCarImpl<IRacingCar>(placeCount, makeOfTheCar)
{
}
