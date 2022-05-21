#pragma once

#include "../../People/IPoliceMan.h"
#include "./ICar.h"

class IPoliceCar : public ICar<IPoliceMan>
{
};
