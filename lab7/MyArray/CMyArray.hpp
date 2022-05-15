#pragma once

#include <cstdlib>

template <typename T>
class CMyArray
{
public:
	using size_type = std::size_t;

	CMyArray();
	CMyArray(size_type size);
	CMyArray(CMyArray const& other);
	CMyArray(CMyArray&& other) noexcept;

	CMyArray& operator=(CMyArray const& other);
	CMyArray& operator=(CMyArray&& other) noexcept;

	~CMyArray();

	void Resize(size_type newSize);
	void Clear();

	size_type GetSize() const
	{
		return m_size;
	}

	// TODO: indexed access, iterators

private:
	T* m_data;
	size_type m_size = 0;
};
