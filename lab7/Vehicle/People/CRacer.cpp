#include "CRacer.h"

CRacer::CRacer(std::string&& name, std::size_t awardsCount)
	: m_name(std::move(name))
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
