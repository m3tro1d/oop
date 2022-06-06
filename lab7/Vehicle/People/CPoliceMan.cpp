#include "CPoliceMan.h"

CPoliceMan::CPoliceMan(std::string const& name, std::string const& departmentName)
	: CPersonImpl<IPoliceMan>(name)
	, m_departmentName(departmentName)
{
}

std::string CPoliceMan::GetDepartmentName() const
{
	return m_departmentName;
}
