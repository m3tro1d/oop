#pragma once

#include "./IRacingCar.h"
#include <vector>

class CRacingCar : public IRacingCar
{
public:
	CRacingCar(std::size_t placeCount, MakeOfTheCar makeOfTheCar);

	bool IsEmpty() const final;
	bool IsFull() const final;

	std::size_t GetPlaceCount() const final;
	std::size_t GetPassengerCount() const final;

	void RemoveAllPassengers() final;

	void AddPassenger(std::shared_ptr<IRacer> passenger) final;

	void RemovePassenger(std::size_t index) final;

	IRacer const& GetPassenger(std::size_t index) const final;

	MakeOfTheCar GetMakeOfTheCar() const final;

private:
	std::size_t m_placeCount;
	MakeOfTheCar m_makeOfTheCar;
	std::vector<std::shared_ptr<IRacer>> m_passengers;
};
