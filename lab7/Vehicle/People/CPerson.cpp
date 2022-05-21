#include "CPerson.h"

CPerson::CPerson(std::string&& name)
	: m_name(std::move(name))
{
}

std::string CPerson::GetName() const
{
	return m_name;
}
