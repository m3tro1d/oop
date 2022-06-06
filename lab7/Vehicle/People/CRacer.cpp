#include "CRacer.h"

CRacer::CRacer(std::string const& name, std::size_t awardsCount)
	: CPersonImpl<IRacer>(name)
	, m_awardsCount(awardsCount)
{
}

std::size_t CRacer::GetAwardsCount() const
{
	return m_awardsCount;
};
