#pragma once

#include <string>

class CStringStack
{
public:
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
	size_t GetSize() const;

private:
	static constexpr size_t REALLOCATION_FACTOR = 2;

	void Reallocate(size_t newSize);

	std::string* m_data = nullptr;
	size_t m_capacity = 1;
	size_t m_size = 0;
};
