#pragma once

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

class CMyString
{
public:
	template <bool IsConst, bool IsStraight>
	class IteratorBase
	{
		friend class IteratorBase<true, IsStraight>;

	public:
		using MyType = IteratorBase<IsConst, IsStraight>;
		using value_type = std::conditional_t<IsConst, char const, char>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		IteratorBase() = default;

		IteratorBase(char* item)
			: m_item(item)
		{
		}

		IteratorBase(IteratorBase<false, IsStraight> const& other)
			: m_item(other.m_item)
		{
		}

		reference operator*() const
		{
			return *m_item;
		}

		MyType& operator+=(difference_type offset)
		{
			if (IsStraight)
			{
				m_item += offset;
			}
			else
			{
				m_item -= offset;
			}

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

		friend bool operator==(MyType const& it1, MyType const& it2)
		{
			return it1.m_item == it2.m_item;
		}

		friend bool operator!=(MyType const& it1, MyType const& it2)
		{
			return !(it1 == it2);
		}

		friend difference_type operator-(MyType const& it1, MyType const& it2)
		{
			return it1.m_item - it2.m_item;
		}

		reference operator[](difference_type index)
		{
			return m_item[index];
		}

	private:
		char* m_item = nullptr;
	};

	using iterator = IteratorBase<false, true>;
	using const_iterator = IteratorBase<true, true>;
	using reverse_iterator = IteratorBase<false, false>;
	using const_reverse_iterator = IteratorBase<true, false>;

	CMyString();
	CMyString(char const* pString);
	CMyString(char const* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(std::string const& stlString);

	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other) noexcept;

	~CMyString() noexcept;

	char const* GetStringData() const;
	size_t GetLength() const;

	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	void Clear();

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();

	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

	CMyString& operator+=(CMyString const& other);

	char const& operator[](size_t index) const;
	char& operator[](size_t index);

	friend std::istream& operator>>(std::istream& stream, CMyString& s);

private:
	char* m_data;
	size_t m_length;
};

CMyString const operator+(CMyString s1, CMyString const& s2);

bool operator==(CMyString const& s1, CMyString const& s2);
bool operator!=(CMyString const& s1, CMyString const& s2);

bool operator<(CMyString const& s1, CMyString const& s2);
bool operator>(CMyString const& s1, CMyString const& s2);

bool operator<=(CMyString const& s1, CMyString const& s2);
bool operator>=(CMyString const& s1, CMyString const& s2);

std::ostream& operator<<(std::ostream& stream, CMyString const& s);
