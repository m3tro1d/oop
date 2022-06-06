#include "CPerson.h"

CPerson::CPerson(std::string const& name)
	: CPersonImpl<IPerson>(name)
{
}
