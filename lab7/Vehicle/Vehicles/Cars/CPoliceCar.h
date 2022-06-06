#pragma once

#include "./IPoliceCar.h"
#include "CCarImpl.h"
#include <vector>

class CPoliceCar : public CCarImpl<IPoliceCar>
{
public:
	CPoliceCar(std::size_t placeCount, MakeOfTheCar makeOfTheCar);
};
