#include "CTaxi.h"

CTaxi::CTaxi(MakeOfTheCar makeOfTheCar)
	: m_makeOfCar(makeOfTheCar)
{
}

void CTaxi::AddPassenger(std::shared_ptr<IPerson> passenger)
{
	m_passengers.push_back(passenger);
}

void CTaxi::RemovePassenger(std::size_t index)
{
	m_passengers.erase(std::next(m_passengers.begin(), index));
}

IPerson const& CTaxi::GetPassenger(std::size_t index) const
{
	return *m_passengers.at(index);
}

MakeOfTheCar CTaxi::GetMakeOfTheCar() const
{
	return m_makeOfCar;
}
