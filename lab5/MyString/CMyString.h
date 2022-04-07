#pragma once

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

class CMyString
{
public:
	class Iterator
	{
	public:
		using ValueType = char;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;

		explicit Iterator(PointerType ptr);

		Iterator& operator++();
		Iterator const operator++(int);

		PointerType operator->() const;
		ReferenceType operator*() const;

		ReferenceType operator[](size_t index) const;

		bool operator==(Iterator const& other) const;
		bool operator!=(Iterator const& other) const;

	private:
		PointerType m_ptr;
	};

	class ConstIterator
	{
	public:
		using ValueType = char;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;

		explicit ConstIterator(PointerType ptr);

		ConstIterator& operator++();
		ConstIterator const operator++(int);

		PointerType operator->() const;
		ReferenceType operator*() const;

		ReferenceType operator[](size_t index) const;

		bool operator==(ConstIterator const& other) const;
		bool operator!=(ConstIterator const& other) const;

	private:
		PointerType m_ptr;
	};

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

	Iterator begin();
	Iterator end();

	ConstIterator cbegin() const;
	ConstIterator cend() const;

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
