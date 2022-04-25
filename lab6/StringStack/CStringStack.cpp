#include "CStringStack.h"

CStringStack::CStringStack(const CStringStack& other)
{
	// TODO
}

CStringStack::CStringStack(CStringStack&& other) noexcept
	: m_data(other.m_data)
	, m_capacity(other.m_capacity)
	, m_size(other.m_size)
{
	other.m_data = nullptr;
	other.m_capacity = 0;
	other.m_size = 0;
}

CStringStack& CStringStack::operator=(CStringStack const& other)
{
	if (std::addressof(other) != this)
	{
		CStringStack copy(other);
		std::swap(m_data, copy.m_data);
		std::swap(m_capacity, copy.m_capacity);
		std::swap(m_size, copy.m_size);
	}
	return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& other) noexcept
{
	if (std::addressof(other) != this)
	{
		delete[] m_data;

		m_data = other.m_data;
		m_capacity = other.m_capacity;
		m_size = other.m_size;

		other.m_data = nullptr;
		other.m_capacity = 0;
		other.m_size = 0;
	}
	return *this;
}

CStringStack::~CStringStack() noexcept
{
	delete[] m_data;
}

void CStringStack::Push(const std::string& str)
{
	// TODO
}

void CStringStack::Push(std::string&& str)
{
	// TODO
}

std::string CStringStack::Top() const
{
	// TODO
	return {};
}

void CStringStack::Pop()
{
	// TODO
}

bool CStringStack::IsEmpty() const
{
	return m_size == 0;
}

size_t CStringStack::GetCapacity() const
{
	return m_capacity;
}

size_t CStringStack::GetSize() const
{
	return m_size;
}

void CStringStack::Reallocate(size_t newSize)
{
	// TODO
}
