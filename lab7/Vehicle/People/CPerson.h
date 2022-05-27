#pragma once

#include "./IPerson.h"

class CPerson : public IPerson
{
public:
	explicit CPerson(std::string const& name);

	std::string GetName() const final;

private:
	std::string m_name;
};
