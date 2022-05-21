#pragma once

#include "../People/IPerson.h"
#include "./IVehicle.h"

class IBus : public IVehicle<IPerson>
{
};
