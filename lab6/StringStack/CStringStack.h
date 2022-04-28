#pragma once

#include "CStringStackUnderflowError.h"
#include <memory>
#include <string>

class CStringStack
{
public:
	using size_type = std::size_t;

	CStringStack() = default;
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
	size_type GetSize() const;

private:
	struct Node
	{
		Node(std::string const& value, std::shared_ptr<Node> const& next)
			: Value(value)
			, Next(next)
		{
		}

		std::string Value;
		std::shared_ptr<Node> Next;
	};

	std::shared_ptr<Node> m_top = nullptr;
	size_type m_size = 0;
};
