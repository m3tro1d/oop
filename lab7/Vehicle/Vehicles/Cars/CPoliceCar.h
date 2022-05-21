#pragma once

#include "./IPoliceCar.h"
#include <vector>

class CPoliceCar : public IPoliceCar
{
public:
	CPoliceCar(MakeOfTheCar makeOfTheCar);

	void AddPassenger(std::shared_ptr<IPoliceMan> passenger) final;

	void RemovePassenger(std::size_t index) final;

	IPoliceMan const& GetPassenger(std::size_t index) const final;

	MakeOfTheCar GetMakeOfTheCar() const final;

private:
	MakeOfTheCar m_makeOfCar;
	std::vector<std::shared_ptr<IPoliceMan>> m_passengers;
};
