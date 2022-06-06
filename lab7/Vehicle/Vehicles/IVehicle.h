#pragma once

#include "./IBasicVehicle.h"
#include <memory>

template <typename Passenger>
class IVehicle : public IBasicVehicle
{
public:
	using PassengerType = Passenger;

	virtual void AddPassenger(std::shared_ptr<Passenger> passenger) = 0;
	virtual void RemovePassenger(std::size_t index) = 0;
	virtual Passenger const& GetPassenger(std::size_t index) const = 0;
};
