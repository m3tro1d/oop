#include "CRacer.h"

CRacer::CRacer(std::string const& name, std::size_t awardsCount)
	: m_name(name)
	, m_awardsCount(awardsCount)
{
}

std::string CRacer::GetName() const
{
	return m_name;
};
std::size_t CRacer::GetAwardsCount() const
{
	return m_awardsCount;
};
