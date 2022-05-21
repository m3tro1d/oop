#pragma once

#include "../../People/IRacer.h"
#include "./ICar.h"

class IRacingCar : public ICar<IRacer>
{
};
