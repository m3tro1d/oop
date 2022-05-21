#include "CPoliceCar.h"

CPoliceCar::CPoliceCar(MakeOfTheCar makeOfTheCar)
	: m_makeOfCar(makeOfTheCar)
{
}

void CPoliceCar::AddPassenger(std::shared_ptr<IPoliceMan> passenger)
{
	m_passengers.push_back(passenger);
}

void CPoliceCar::RemovePassenger(std::size_t index)
{
	m_passengers.erase(std::next(m_passengers.begin(), index));
}

IPoliceMan const& CPoliceCar::GetPassenger(std::size_t index) const
{
	return *m_passengers.at(index);
}

MakeOfTheCar CPoliceCar::GetMakeOfTheCar() const
{
	return m_makeOfCar;
}
