#pragma once

#include "./IPerson.h"

class IRacer : public IPerson
{
public:
	virtual std::size_t GetAwardsCount() const = 0;
};
