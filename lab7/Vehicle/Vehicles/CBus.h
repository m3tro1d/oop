#pragma once

#include "./IBus.h"
#include <vector>

class CBus : public IBus
{
public:
	void AddPassenger(std::shared_ptr<IPerson> passenger) final;

	void RemovePassenger(std::size_t index) final;

	IPerson const& GetPassenger(std::size_t index) const final;

private:
	std::vector<std::shared_ptr<IPerson>> m_passengers;
};
