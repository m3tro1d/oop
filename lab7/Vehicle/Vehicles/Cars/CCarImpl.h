#pragma once

#include "../CVehicleImpl.h"
#include "ICar.h"

template <class Base, class Passenger>
class CCarImpl : public CVehicleImpl<Base, Passenger>
{
public:
	CCarImpl(std::size_t placeCount, MakeOfTheCar makeOfTheCar)
		: CVehicleImpl<Base, Passenger>(placeCount)
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
