#pragma once

#include "./IPoliceCar.h"
#include "CCarImpl.hpp"
#include <vector>

class CPoliceCar : public CCarImpl<IPoliceCar>
{
public:
	CPoliceCar(std::size_t placeCount, MakeOfTheCar makeOfTheCar);
};
