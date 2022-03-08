#pragma once

#include <regex>
#include <limits>
#include <map>
#include <string>

class CCalculator
{
public:
	using Identifier = std::string;
	using Value = double;

	enum class Operation
	{
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

	using Variables = std::map<Identifier, Value>;
	using Functions = std::map<Identifier, Expression>;

	static constexpr Value NAN_VALUE = std::numeric_limits<Value>::signaling_NaN();

public:
	void CreateVariable(const Identifier& identifier);
	void AssignVariable(const Identifier& identifier, Value value);
	void AssignVariable(const Identifier& identifier, const Identifier& assignedIdentifier);

	void CreateFunction(const Identifier& identifier, const Expression& expression);

	Value GetIdentifierValue(const Identifier& identifier) const;

	Variables DumpVariables() const;
	Variables DumpFunctions() const;

private:
	static bool IsValidIdentifier(const Identifier& identifier);
	bool DoesIdentifierExist(const Identifier& identifier) const;

private:
	Variables m_variables;
	Functions m_functions;
};
