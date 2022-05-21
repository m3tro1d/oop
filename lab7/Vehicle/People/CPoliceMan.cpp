#include "CPoliceMan.h"

CPoliceMan::CPoliceMan(std::string&& name, std::string&& departmentName)
	: m_name(std::move(name))
	, m_departmentName(std::move(departmentName))
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
