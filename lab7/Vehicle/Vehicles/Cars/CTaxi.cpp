#include "CTaxi.h"

bool CTaxi::IsEmpty() const
{
	return m_passengers.empty();
}

bool CTaxi::IsFull() const
{
	return m_passengers.size() == PLACE_COUNT;
}

std::size_t CTaxi::GetPlaceCount() const
{
	return PLACE_COUNT;
}

std::size_t CTaxi::GetPassengerCount() const
{
	return m_passengers.size();
}

void CTaxi::RemoveAllPassengers()
{
	m_passengers.clear();
}

CTaxi::CTaxi(MakeOfTheCar makeOfTheCar)
	: m_makeOfTheCar(makeOfTheCar)
{
}

void CTaxi::AddPassenger(std::shared_ptr<IPerson> passenger)
{
	if (IsFull())
	{
		throw std::logic_error("no more places");
	}

	m_passengers.push_back(passenger);
}

void CTaxi::RemovePassenger(std::size_t index)
{
	if (IsEmpty())
	{
		throw std::logic_error("no passengers");
	}

	m_passengers.erase(std::next(m_passengers.begin(), index));
}

IPerson const& CTaxi::GetPassenger(std::size_t index) const
{
	return *m_passengers.at(index);
}

MakeOfTheCar CTaxi::GetMakeOfTheCar() const
{
	return m_makeOfTheCar;
}
