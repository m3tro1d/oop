#pragma once

#include <algorithm>
#include <stdexcept>
#include <type_traits>

template <typename T>
class CMyArray
{
public:
	template <bool IsConst>
	class IteratorBase : public std::iterator<std::bidirectional_iterator_tag, std::conditional_t<IsConst, T const, T>>
	{
	public:
		using MyType = IteratorBase<IsConst>;
		using value_type = std::conditional_t<IsConst, T const, T>;
		using reference = value_type&;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;

		IteratorBase() = default;

		IteratorBase(T* item)
			: m_item(item)
		{
		}

		reference operator*() const
		{
			return *m_item;
		}

		MyType& operator+=(difference_type offset)
		{
			m_item += offset;
			return *this;
		}

		MyType operator+(difference_type offset) const
		{
			MyType self(m_item);
			return self += offset;
		}

		friend MyType operator+(difference_type offset, MyType const& it)
		{
			return it + offset;
		}

		MyType& operator++()
		{
			return *this += 1;
		}

		MyType operator++(int)
		{
			auto self = *this;
			++(*this);
			return self;
		}

		MyType& operator-=(difference_type offset)
		{
			m_item -= offset;
			return *this;
		}

		MyType operator-(difference_type offset) const
		{
			MyType self(m_item);
			return self -= offset;
		}

		friend MyType operator-(difference_type offset, MyType const& it)
		{
			return it - offset;
		}

		MyType& operator--()
		{
			return *this -= 1;
		}

		MyType operator--(int)
		{
			auto self = *this;
			--(*this);
			return self;
		}

		friend bool operator==(MyType const& it1, MyType const& it2)
		{
			return it1.m_item == it2.m_item;
		}

		friend bool operator!=(MyType const& it1, MyType const& it2)
		{
			return !(it1 == it2);
		}

	private:
		T* m_item = nullptr;
	};

	using size_type = std::size_t;
	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;
	using reverse_iterator = std::reverse_iterator<IteratorBase<false>>;
	using const_reverse_iterator = std::reverse_iterator<IteratorBase<true>>;

	CMyArray() = default;

	explicit CMyArray(size_type size)
		: m_data(new T[size])
		, m_size(size)
	{
	}

	CMyArray(CMyArray const& other)
		: m_data(new T[other.m_size])
		, m_size(other.m_size)
	{
		std::copy(other.m_data, other.m_data + other.m_size, m_data);
	}

	CMyArray(CMyArray&& other) noexcept
		: m_data(other.m_data)
		, m_size(other.m_size)
	{
		other.m_data = nullptr;
		other.m_size = 0;
	}

	CMyArray& operator=(CMyArray const& other)
	{
		if (std::addressof(other) != this)
		{
			CMyArray copy(other);
			std::swap(m_data, copy.m_data);
			std::swap(m_size, copy.m_size);
		}
		return *this;
	}

	CMyArray& operator=(CMyArray&& other) noexcept
	{
		if (std::addressof(other) != this)
		{
			delete[] m_data;

			m_data = other.m_data;
			m_size = other.m_size;

			other.m_data = nullptr;
			other.m_size = 0;
		}
		return *this;
	}

	~CMyArray()
	{
		delete[] m_data;
	}

	void Push(T const& element)
	{
		Resize(m_size + 1);
		m_data[m_size - 1] = element;
	}

	void Push(T&& element)
	{
		Resize(m_size + 1);
		m_data[m_size - 1] = std::move(element);
	}

	void Resize(size_type newSize)
	{
		T* newData = new T[newSize];

		if (newSize < m_size)
		{
			std::copy_n(m_data, newSize, newData);
		}
		else
		{
			std::copy(m_data, m_data + m_size, newData);
		}

		delete[] m_data;

		m_data = newData;
		m_size = newSize;
	}

	void Clear()
	{
		delete[] m_data;

		m_data = nullptr;
		m_size = 0;
	}

	size_type GetSize() const
	{
		return m_size;
	}

	T const& operator[](size_type index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("index out of range");
		}

		return m_data[index];
	}

	T& operator[](size_type index)
	{
		if (index >= m_size)
		{
			throw std::out_of_range("index out of range");
		}

		return m_data[index];
	}

	iterator begin()
	{
		return m_data;
	}

	iterator end()
	{
		return m_data + m_size;
	}

	const_iterator begin() const
	{
		return m_data;
	}

	const_iterator end() const
	{
		return m_data + m_size;
	}

	const_iterator cbegin() const
	{
		return m_data;
	}

	const_iterator cend() const
	{
		return m_data + m_size;
	}

	reverse_iterator rbegin()
	{
		return m_data + m_size - 1;
	}

	reverse_iterator rend()
	{
		return m_data - 1;
	}

	const_reverse_iterator crbegin() const
	{
		return m_data + m_size - 1;
	}

	const_reverse_iterator crend() const
	{
		return m_data - 1;
	}

private:
	T* m_data = nullptr;
	size_type m_size = 0;
};
