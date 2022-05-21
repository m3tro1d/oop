#pragma once

#include "./IRacingCar.h"
#include <vector>

class CRacingCar : public IRacingCar
{
public:
	CRacingCar(MakeOfTheCar makeOfTheCar);

	void AddPassenger(std::shared_ptr<IRacer> passenger) final;

	void RemovePassenger(std::size_t index) final;

	IRacer const& GetPassenger(std::size_t index) const final;

	MakeOfTheCar GetMakeOfTheCar() const final;

private:
	MakeOfTheCar m_makeOfCar;
	std::vector<std::shared_ptr<IRacer>> m_passengers;
};
