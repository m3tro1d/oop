#pragma once

#include "../People/IPerson.h"
#include <memory>
#include <type_traits>
#include <vector>

template <class Base>
class CVehicleImpl : public Base
{
public:
	explicit CVehicleImpl(std::size_t placeCount)
		: m_placeCount(placeCount)
	{
	}

	bool IsEmpty() const final
	{
		return m_passengers.empty();
	}

	bool IsFull() const final
	{
		return m_passengers.size() == m_placeCount;
	}

	std::size_t GetPlaceCount() const final
	{
		return m_placeCount;
	}

	std::size_t GetPassengerCount() const final
	{
		return m_passengers.size();
	}

	void RemoveAllPassengers() final
	{
		m_passengers.clear();
	}

	void AddPassenger(std::shared_ptr<typename Base::PassengerType> passenger) final
	{
		if (IsFull())
		{
			throw std::logic_error("no more places");
		}

		m_passengers.push_back(passenger);
	}

	void RemovePassenger(std::size_t index) final
	{
		if (IsEmpty())
		{
			throw std::logic_error("no passengers");
		}

		m_passengers.erase(std::next(m_passengers.begin(), index));
	}

	typename Base::PassengerType const& GetPassenger(std::size_t index) const final
	{
		return *m_passengers.at(index);
	}

private:
	std::size_t m_placeCount;
	std::vector<std::shared_ptr<typename Base::PassengerType>> m_passengers;
};
