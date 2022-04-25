#pragma once

#include <string>

class CStringStack
{
public:
	CStringStack();
	CStringStack(CStringStack const& other);
	CStringStack(CStringStack&& other) noexcept;

	CStringStack& operator=(CStringStack const& other);
	CStringStack& operator=(CStringStack&& other) noexcept;

	~CStringStack() noexcept;

	void Push(std::string const& str);
	void Push(std::string&& str);
	std::string Top() const;
	void Pop();

	bool IsEmpty() const;
	size_t Size() const;
};
