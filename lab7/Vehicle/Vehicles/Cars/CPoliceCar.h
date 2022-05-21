#pragma once

#include "./IPoliceCar.h"
#include <vector>

class CPoliceCar : public IPoliceCar
{
public:
	explicit CPoliceCar(MakeOfTheCar makeOfTheCar);

	bool IsEmpty() const final;
	bool IsFull() const final;

	std::size_t GetPlaceCount() const final;
	std::size_t GetPassengerCount() const final;

	void RemoveAllPassengers() final;

	void AddPassenger(std::shared_ptr<IPoliceMan> passenger) final;

	void RemovePassenger(std::size_t index) final;

	IPoliceMan const& GetPassenger(std::size_t index) const final;

	MakeOfTheCar GetMakeOfTheCar() const final;

private:
	static const std::size_t PLACE_COUNT = 4;

	MakeOfTheCar m_makeOfTheCar;
	std::vector<std::shared_ptr<IPoliceMan>> m_passengers;
};
