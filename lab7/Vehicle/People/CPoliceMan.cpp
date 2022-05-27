#include "CPoliceMan.h"

CPoliceMan::CPoliceMan(std::string const& name, std::string const& departmentName)
	: m_name(name)
	, m_departmentName(departmentName)
{
}

std::string CPoliceMan::GetName() const
{
	return m_name;
}

std::string CPoliceMan::GetDepartmentName() const
{
	return m_departmentName;
}
