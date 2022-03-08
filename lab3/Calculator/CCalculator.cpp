#include "CCalculator.h"

void CCalculator::CreateVariable(const CCalculator::Identifier& identifier)
{
	if (!IsValidIdentifier(identifier))
	{
		throw std::invalid_argument("invalid identifier");
	}

	if (DoesIdentifierExist(identifier))
	{
		throw std::runtime_error("identifier already exists");
	}

	m_variables[identifier] = NAN_VALUE;
}

void CCalculator::AssignVariable(const CCalculator::Identifier& identifier, CCalculator::Value value)
{
	if (!DoesIdentifierExist(identifier))
	{
		CreateVariable(identifier);
	}

	m_variables[identifier] = value;
}

void CCalculator::AssignVariable(const CCalculator::Identifier& identifier, const CCalculator::Identifier& assignedIdentifier)
{
	if (!DoesIdentifierExist(assignedIdentifier))
	{
		throw std::runtime_error("identifier does not exist");
	}
	if (!DoesIdentifierExist(identifier))
	{
		CreateVariable(identifier);
	}

	m_variables[identifier] = m_variables[assignedIdentifier];
}

void CCalculator::CreateFunction(const CCalculator::Identifier& identifier, const CCalculator::Expression& expression)
{
	// TODO
}

CCalculator::Value CCalculator::GetIdentifierValue(const CCalculator::Identifier& identifier) const
{
	// TODO: process functions
	if (!DoesIdentifierExist(identifier))
	{
		throw std::runtime_error("identifier does not exist");
	}

	return m_variables.at(identifier);
}

CCalculator::IdentifierValues CCalculator::DumpVariables() const
{
	return m_variables;
}

CCalculator::IdentifierValues CCalculator::DumpFunctions() const
{
	// TODO
	return {};
}

bool CCalculator::IsValidIdentifier(const CCalculator::Identifier& identifier)
{
	std::regex identifierRegex(
		R"([A-Za-z_][0-9A-Za-z_]*)",
		std::regex::icase);
	return std::regex_match(identifier, identifierRegex);
}

bool CCalculator::DoesIdentifierExist(const CCalculator::Identifier& identifier) const
{
	return m_variables.find(identifier) != m_variables.end();
}
