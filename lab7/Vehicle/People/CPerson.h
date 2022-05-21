#pragma once

#include "./IPerson.h"

class CPerson : public IPerson
{
public:
	CPerson(std::string&& name);

	std::string GetName() const final;

private:
	std::string m_name;
};
