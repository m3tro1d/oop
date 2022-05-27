#pragma once

#include "./CPerson.h"
#include "./IPoliceMan.h"

class CPoliceMan : public IPoliceMan
{
public:
	CPoliceMan(std::string const& name, std::string const& departmentName);

	std::string GetName() const final;

	std::string GetDepartmentName() const final;

private:
	std::string m_name;
	std::string m_departmentName;
};
