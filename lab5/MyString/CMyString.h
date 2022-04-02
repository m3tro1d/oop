#pragma once

#include <string>

class CMyString
{
	CMyString();
	CMyString(char const* pString);
	CMyString(char const* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other);
	CMyString(std::string const& stlString);

	~CMyString();

	size_t GetLength() const;
	char const* GetStringData() const;

	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	void Clear();

	CMyString& operator=(CMyString const& other);

	friend CMyString const operator+(CMyString const& s1, CMyString const& s2);
	// TODO: other operators
};
