#include "CBus.h"

void CBus::AddPassenger(std::shared_ptr<IPerson> passenger)
{
	m_passengers.push_back(passenger);
}

void CBus::RemovePassenger(std::size_t index)
{
	m_passengers.erase(std::next(m_passengers.begin(), index));
}

IPerson const& CBus::GetPassenger(std::size_t index) const
{
	return *m_passengers.at(index);
}
