#include "CBus.h"

bool CBus::IsEmpty() const
{
	return m_passengers.empty();
}

bool CBus::IsFull() const
{
	return m_passengers.size() == PLACE_COUNT;
}

std::size_t CBus::GetPlaceCount() const
{
	return PLACE_COUNT;
}

std::size_t CBus::GetPassengerCount() const
{
	return m_passengers.size();
}

void CBus::RemoveAllPassengers()
{
	m_passengers.clear();
}

void CBus::AddPassenger(std::shared_ptr<IPerson> passenger)
{
	if (IsFull())
	{
		throw std::logic_error("no more places");
	}

	m_passengers.push_back(passenger);
}

void CBus::RemovePassenger(std::size_t index)
{
	if (IsEmpty())
	{
		throw std::logic_error("no passengers");
	}

	m_passengers.erase(std::next(m_passengers.begin(), index));
}

IPerson const& CBus::GetPassenger(std::size_t index) const
{
	return *m_passengers.at(index);
}
