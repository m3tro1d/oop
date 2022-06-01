#pragma once

#include <type_traits>

class IBasicVehicle
{
public:
	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;

	virtual std::size_t GetPlaceCount() const = 0;
	virtual std::size_t GetPassengerCount() const = 0;

	virtual void RemoveAllPassengers() = 0;

	virtual ~IBasicVehicle() = default;
};
