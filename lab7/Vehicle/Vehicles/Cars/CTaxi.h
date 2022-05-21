#pragma once

#include "./ITaxi.h"
#include <vector>

class CTaxi : public ITaxi
{
public:
	bool IsEmpty() const final;
	bool IsFull() const final;

	std::size_t GetPlaceCount() const final;
	std::size_t GetPassengerCount() const final;

	void RemoveAllPassengers() final;

	explicit CTaxi(MakeOfTheCar makeOfTheCar);

	void AddPassenger(std::shared_ptr<IPerson> passenger) final;

	void RemovePassenger(std::size_t index) final;

	IPerson const& GetPassenger(std::size_t index) const final;

	MakeOfTheCar GetMakeOfTheCar() const final;

private:
	static const std::size_t PLACE_COUNT = 4;

	MakeOfTheCar m_makeOfTheCar;
	std::vector<std::shared_ptr<IPerson>> m_passengers;
};
