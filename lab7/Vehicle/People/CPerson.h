#pragma once

#include "./IPerson.h"
#include "CPersonImpl.h"

class CPerson : public CPersonImpl<IPerson>
{
public:
	explicit CPerson(std::string const& name);
};
