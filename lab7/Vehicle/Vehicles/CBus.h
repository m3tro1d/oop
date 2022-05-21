#pragma once

#include "./IBus.h"
#include <vector>

class CBus : public IBus
{
public:
	bool IsEmpty() const final;
	bool IsFull() const final;

	std::size_t GetPlaceCount() const final;
	std::size_t GetPassengerCount() const final;

	void RemoveAllPassengers() final;

	void AddPassenger(std::shared_ptr<IPerson> passenger) final;

	void RemovePassenger(std::size_t index) final;

	IPerson const& GetPassenger(std::size_t index) const final;

private:
	static const std::size_t PLACE_COUNT = 20;

	std::vector<std::shared_ptr<IPerson>> m_passengers;
};
