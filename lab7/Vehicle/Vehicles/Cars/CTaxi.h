#pragma once

#include "./ITaxi.h"
#include <vector>

class CTaxi : public ITaxi
{
public:
	CTaxi(MakeOfTheCar makeOfTheCar);

	void AddPassenger(std::shared_ptr<IPerson> passenger) final;

	void RemovePassenger(std::size_t index) final;

	IPerson const& GetPassenger(std::size_t index) const final;

	MakeOfTheCar GetMakeOfTheCar() const final;

private:
	MakeOfTheCar m_makeOfCar;
	std::vector<std::shared_ptr<IPerson>> m_passengers;
};
