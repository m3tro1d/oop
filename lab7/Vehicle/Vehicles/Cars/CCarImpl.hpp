#pragma once

#include "../CVehicleImpl.hpp"
#include "ICar.h"

template <class Base>
class CCarImpl : public CVehicleImpl<Base>
{
public:
	CCarImpl(std::size_t placeCount, MakeOfTheCar makeOfTheCar)
		: CVehicleImpl<Base>(placeCount)
		, m_makeOfTheCar(makeOfTheCar)
	{
	}

	MakeOfTheCar GetMakeOfTheCar() const final
	{
		return m_makeOfTheCar;
	}

private:
	MakeOfTheCar m_makeOfTheCar;
};
