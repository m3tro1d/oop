#pragma once

#include "../IVehicle.h"

enum class MakeOfTheCar
{
	BMW,
	MITSUBISHI,
	FORD,
	MERCEDES,
	TOYOTA,
	KIA,
	FERRARI,
	PORSCHE,
	LEXUS,
	NISSAN,
	INIFINITI,
};

template <typename Passenger>
class ICar : public IVehicle<Passenger>
{
public:
	virtual MakeOfTheCar GetMakeOfTheCar() const = 0;
};
