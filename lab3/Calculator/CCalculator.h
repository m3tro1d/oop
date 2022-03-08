#pragma once

#include <limits>
#include <map>
#include <string>

class CCalculator
{
public:
	using Identifier = std::string;
	using Value = double;
	using Expression = std::string;

	using Variables = std::map<Identifier, Value>;
	using Functions = std::map<Identifier, Expression>;

	static constexpr Value NON_EXISTING_VALUE = std::numeric_limits<Value>::signaling_NaN();

public:
	void CreateVariable(const Identifier& identifier);
	void AssignVariable(const Identifier& identifier, const Expression& value);

	void CreateFunction(const Identifier& identifier, const Expression& expression);

	Value CalculateValueByIdentifier(const Identifier& identifier);

	Variables DumpVariables() const;
	Functions DumpFunctions() const;

private:
	bool IsValidIdentifier(const Identifier& identifier) const;
	bool DoesIdentifierExist(const Identifier& identifier) const;

private:
	Variables m_variables;
	Functions m_functions;
};
