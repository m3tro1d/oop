#pragma once

#include "./IRacer.h"
#include "CPersonImpl.h"

class CRacer : public CPersonImpl<IRacer>
{
public:
	CRacer(std::string const& name, std::size_t awardsCount);

	std::size_t GetAwardsCount() const final;

private:
	std::size_t m_awardsCount;
};
