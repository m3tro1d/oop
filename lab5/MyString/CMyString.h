#pragma once

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

class CMyString
{
public:
	template <bool IsConst>
	class IteratorBase
	{
		friend class IteratorBase<true>;

	public:
		using MyType = IteratorBase<IsConst>;
		using ValueType = std::conditional_t<IsConst, char const, char>;
		using ReferenceType = ValueType&;
		using DifferenceType = std::ptrdiff_t;
		using IteratorCategory = std::random_access_iterator_tag;

		IteratorBase() = default;

		IteratorBase(char* item)
			: m_item(item)
		{
		}

		IteratorBase(IteratorBase<false> const& other)
			: m_item(other.m_item)
		{
		}

		ReferenceType operator*() const
		{
			return *m_item;
		}

		MyType& operator+=(DifferenceType offset)
		{
			m_item += offset;
			return *this;
		}

		MyType operator+(DifferenceType offset) const
		{
			MyType self(m_item);
			return self += offset;
		}

		friend MyType operator+(DifferenceType offset, MyType const& it)
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

	private:
		char* m_item = nullptr;
	};

	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;

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

	CMyString&
	operator+=(CMyString const& other);

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
