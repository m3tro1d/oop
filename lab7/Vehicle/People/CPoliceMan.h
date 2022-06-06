#pragma once

#include "./IPoliceMan.h"
#include "CPersonImpl.h"

class CPoliceMan : public CPersonImpl<IPoliceMan>
{
public:
	CPoliceMan(std::string const& name, std::string const& departmentName);

	std::string GetDepartmentName() const final;

private:
	std::string m_departmentName;
};
