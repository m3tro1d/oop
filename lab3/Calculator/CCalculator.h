#pragma once

#include <cfenv>
#include <limits>
#include <map>
#include <regex>
#include <string>

class CCalculator
{
public:
	using Identifier = std::string;
	using Value = double;

	enum class Operation
	{
		NOTHING,
		ADDITION,
		SUBTRACTION,
		MULTIPLICATION,
		DIVISION,
	};
	using Arguments = std::pair<Identifier, Identifier>;
	using Expression = struct
	{
		Operation operation;
		Arguments arguments;
	};

	using IdentifierValues = std::map<Identifier, Value>;
	using Functions = std::map<Identifier, Expression>;

	static constexpr Value NAN_VALUE = std::numeric_limits<Value>::signaling_NaN();

	void CreateVariable(const Identifier& identifier);
	void AssignVariable(const Identifier& identifier, Value value);
	void AssignVariable(const Identifier& identifier, const Identifier& assignedIdentifier);

	void CreateFunction(const Identifier& identifier, const Identifier& assignedIdentifier);
	void CreateFunction(const Identifier& identifier, const Expression& expression);

	Value GetIdentifierValue(const Identifier& identifier) const;

	const IdentifierValues& DumpVariables() const;
	IdentifierValues DumpFunctions() const;

private:
	static bool IsValidIdentifier(const Identifier& identifier);
	bool DoesIdentifierExist(const Identifier& identifier) const;
	static bool IsZero(Value value);

	Value CalculateExpression(const Expression& expression) const;
	Value CalculateExpressionWithCache(IdentifierValues& cache, const Expression& expression) const;
	Value GetIdentifierValueWithCache(IdentifierValues& cache, const Identifier& identifier) const;

	IdentifierValues m_variables;
	Functions m_functions;
};
