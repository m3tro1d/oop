#include "CRacingCar.h"

CRacingCar::CRacingCar(std::size_t placeCount, MakeOfTheCar makeOfTheCar)
	: m_placeCount(placeCount)
	, m_makeOfTheCar(makeOfTheCar)
{
}

bool CRacingCar::IsEmpty() const
{
	return m_passengers.empty();
}

bool CRacingCar::IsFull() const
{
	return m_passengers.size() == m_placeCount;
}

std::size_t CRacingCar::GetPlaceCount() const
{
	return m_placeCount;
}

std::size_t CRacingCar::GetPassengerCount() const
{
	return m_passengers.size();
}

void CRacingCar::RemoveAllPassengers()
{
	m_passengers.clear();
}

void CRacingCar::AddPassenger(std::shared_ptr<IRacer> passenger)
{
	if (IsFull())
	{
		throw std::logic_error("no more places");
	}

	m_passengers.push_back(passenger);
}

void CRacingCar::RemovePassenger(std::size_t index)
{
	if (IsEmpty())
	{
		throw std::logic_error("no passengers");
	}

	m_passengers.erase(std::next(m_passengers.begin(), index));
}

IRacer const& CRacingCar::GetPassenger(std::size_t index) const
{
	return *m_passengers.at(index);
}

MakeOfTheCar CRacingCar::GetMakeOfTheCar() const
{
	return m_makeOfTheCar;
}
