#pragma once

#include "./IBus.h"
#include <vector>

class CBus : public IBus
{
public:
	explicit CBus(std::size_t placeCount);

	bool IsEmpty() const final;
	bool IsFull() const final;

	std::size_t GetPlaceCount() const final;
	std::size_t GetPassengerCount() const final;

	void RemoveAllPassengers() final;

	void AddPassenger(std::shared_ptr<IPerson> passenger) final;

	void RemovePassenger(std::size_t index) final;

	IPerson const& GetPassenger(std::size_t index) const final;

private:
	std::size_t m_placeCount;
	std::vector<std::shared_ptr<IPerson>> m_passengers;
};
