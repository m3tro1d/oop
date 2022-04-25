#pragma once

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
	size_type GetCapacity() const;
	size_type GetSize() const;

private:
	static constexpr size_type REALLOCATION_FACTOR = 2;

	void Reallocate(size_type newSize);

	std::string* m_data = nullptr;
	size_type m_capacity = 0;
	size_type m_size = 0;
};
