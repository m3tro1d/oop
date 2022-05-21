#pragma once

#include "../../People/IPerson.h"
#include "./ICar.h"

class ITaxi : public ICar<IPerson>
{
};
