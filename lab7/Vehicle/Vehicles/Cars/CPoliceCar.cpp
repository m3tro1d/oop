#include "CPoliceCar.h"

CPoliceCar::CPoliceCar(std::size_t placeCount, MakeOfTheCar makeOfTheCar)
	: m_placeCount(placeCount)
	, m_makeOfTheCar(makeOfTheCar)
{
}

bool CPoliceCar::IsEmpty() const
{
	return m_passengers.empty();
}

bool CPoliceCar::IsFull() const
{
	return m_passengers.size() == m_placeCount;
}

std::size_t CPoliceCar::GetPlaceCount() const
{
	return m_placeCount;
}

std::size_t CPoliceCar::GetPassengerCount() const
{
	return m_passengers.size();
}

void CPoliceCar::RemoveAllPassengers()
{
	m_passengers.clear();
}

void CPoliceCar::AddPassenger(std::shared_ptr<IPoliceMan> passenger)
{
	if (IsFull())
	{
		throw std::logic_error("no more places");
	}

	m_passengers.push_back(passenger);
}

void CPoliceCar::RemovePassenger(std::size_t index)
{
	if (IsEmpty())
	{
		throw std::logic_error("no passengers");
	}

	m_passengers.erase(std::next(m_passengers.begin(), index));
}

IPoliceMan const& CPoliceCar::GetPassenger(std::size_t index) const
{
	return *m_passengers.at(index);
}

MakeOfTheCar CPoliceCar::GetMakeOfTheCar() const
{
	return m_makeOfTheCar;
}
