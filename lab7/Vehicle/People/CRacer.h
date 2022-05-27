#pragma once

#include "./IRacer.h"

class CRacer : public IRacer
{
public:
	CRacer(std::string const& name, std::size_t awardsCount);

	std::string GetName() const final;

	std::size_t GetAwardsCount() const final;

private:
	std::string m_name;
	std::size_t m_awardsCount;
};
