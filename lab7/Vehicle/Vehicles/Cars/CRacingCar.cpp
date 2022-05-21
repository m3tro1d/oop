#include "CRacingCar.h"

CRacingCar::CRacingCar(MakeOfTheCar makeOfTheCar)
	: m_makeOfCar(makeOfTheCar)
{
}

void CRacingCar::AddPassenger(std::shared_ptr<IRacer> passenger)
{
	m_passengers.push_back(passenger);
}

void CRacingCar::RemovePassenger(std::size_t index)
{
	m_passengers.erase(std::next(m_passengers.begin(), index));
}

IRacer const& CRacingCar::GetPassenger(std::size_t index) const
{
	return *m_passengers.at(index);
}

MakeOfTheCar CRacingCar::GetMakeOfTheCar() const
{
	return m_makeOfCar;
}
