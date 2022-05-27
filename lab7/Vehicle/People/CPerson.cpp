#include "CPerson.h"

CPerson::CPerson(std::string const& name)
	: m_name(name)
{
}

std::string CPerson::GetName() const
{
	return m_name;
}
