#pragma once

#include <string>

template <class Base>
class CPersonImpl : public Base
{
public:
	explicit CPersonImpl(std::string const& name)
		: m_name(name)
	{
	}

	std::string GetName() const final
	{
		return m_name;
	}

private:
	std::string m_name;
};
