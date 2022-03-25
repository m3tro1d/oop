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
	if (identifier == assignedIdentifier)
	{
		throw std::invalid_argument("can not assign variable to itself");
	}

	if (!DoesIdentifierExist(identifier))
	{
		CreateVariable(identifier);
	}

	m_variables[identifier] = GetIdentifierValue(assignedIdentifier);
}

void CCalculator::CreateFunction(const CCalculator::Identifier& identifier, const CCalculator::Identifier& assignedIdentifier)
{
	if (!IsValidIdentifier(identifier))
	{
		throw std::invalid_argument("invalid identifier");
	}

	if (DoesIdentifierExist(identifier))
	{
		throw std::runtime_error("identifier already exists");
	}

	if (!DoesIdentifierExist(assignedIdentifier))
	{
		throw std::runtime_error("identifier does not exist");
	}

	Expression expression{
		.operation = Operation::NOTHING,
		.arguments = { assignedIdentifier, "" },
	};
	m_functions[identifier] = expression;
}

void CCalculator::CreateFunction(const CCalculator::Identifier& identifier, const CCalculator::Expression& expression)
{
	if (!IsValidIdentifier(identifier))
	{
		throw std::invalid_argument("invalid identifier");
	}

	if (DoesIdentifierExist(identifier))
	{
		throw std::runtime_error("identifier already exists");
	}

	auto const& args = expression.arguments;
	if (!DoesIdentifierExist(args.first) || !DoesIdentifierExist(args.second))
	{
		throw std::runtime_error("expression contains non-existing identifiers");
	}

	m_functions[identifier] = expression;
}

CCalculator::Value CCalculator::GetIdentifierValue(const CCalculator::Identifier& identifier) const
{
	if (!DoesIdentifierExist(identifier))
	{
		throw std::runtime_error("identifier does not exist");
	}

	auto const variable = m_variables.find(identifier);
	if (variable != m_variables.end())
	{
		return variable->second;
	}

	std::feclearexcept(FE_ALL_EXCEPT);

	auto const result = CalculateExpression(m_functions.at(identifier));

	if (std::fetestexcept(FE_OVERFLOW) || std::fetestexcept(FE_UNDERFLOW))
	{
		throw std::out_of_range("function result overflow");
	}

	return result;
}

const CCalculator::IdentifierValues& CCalculator::DumpVariables() const
{
	return m_variables;
}

CCalculator::IdentifierValues CCalculator::DumpFunctions() const
{
	std::feclearexcept(FE_ALL_EXCEPT);

	IdentifierValues result;
	for (auto const& [identifier, expression] : m_functions)
	{
		result[identifier] = CalculateExpression(expression);
	}

	if (std::fetestexcept(FE_OVERFLOW) || std::fetestexcept(FE_UNDERFLOW))
	{
		throw std::out_of_range("function result overflow");
	}

	return result;
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
	if (m_variables.find(identifier) != m_variables.end())
	{
		return true;
	}

	return m_functions.find(identifier) != m_functions.end();
}

bool CCalculator::IsZero(CCalculator::Value value)
{
	return std::abs(value) < std::numeric_limits<Value>::epsilon();
}

CCalculator::Value CCalculator::CalculateExpression(const CCalculator::Expression& expression) const
{
	IdentifierValues cache;
	return CalculateExpressionWithCache(cache, expression);
}

CCalculator::Value CCalculator::CalculateExpressionWithCache(IdentifierValues& cache, const CCalculator::Expression& expression) const
{
	auto const argument1 = expression.arguments.first;
	auto const argument2 = expression.arguments.second;

	switch (expression.operation)
	{
	case Operation::NOTHING:
		return GetIdentifierValueWithCache(cache, argument1);
	case Operation::ADDITION:
		return GetIdentifierValueWithCache(cache, argument1) + GetIdentifierValueWithCache(cache, argument2);
	case Operation::SUBTRACTION:
		return GetIdentifierValueWithCache(cache, argument1) - GetIdentifierValueWithCache(cache, argument2);
	case Operation::MULTIPLICATION:
		return GetIdentifierValueWithCache(cache, argument1) * GetIdentifierValueWithCache(cache, argument2);
	case Operation::DIVISION: {
		auto const divisor = GetIdentifierValueWithCache(cache, argument2);
		if (IsZero(divisor))
		{
			return NAN_VALUE;
		}
		return GetIdentifierValueWithCache(cache, argument1) / divisor;
	}
	default:
		return NAN_VALUE;
	}
}

CCalculator::Value CCalculator::GetIdentifierValueWithCache(CCalculator::IdentifierValues& cache, const CCalculator::Identifier& identifier) const
{
	auto const value = cache.find(identifier);
	if (value != cache.end())
	{
		return value->second;
	}

	if (!DoesIdentifierExist(identifier))
	{
		throw std::runtime_error("identifier does not exist");
	}

	auto const variable = m_variables.find(identifier);
	if (variable != m_variables.end())
	{
		return variable->second;
	}

	auto const result = CalculateExpressionWithCache(cache, m_functions.at(identifier));
	cache[identifier] = result;

	return result;
}
