#pragma once

#include <cstring>
#include <string>

class CMyString
{
public:
	CMyString();
	CMyString(char const* pString);
	CMyString(char const* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(std::string const& stlString);

	~CMyString();

	size_t GetLength() const;
	char const* GetStringData() const;

	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	void Clear();

	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other) noexcept;

private:
	char* m_data;
	size_t m_length;
};
