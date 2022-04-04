#pragma once

#include <cstring>
#include <stdexcept>
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

	~CMyString() noexcept;

	size_t GetLength() const;
	char const* GetStringData() const;

	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	void Clear();

	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other) noexcept;

	// TODO
	// friend CMyString const operator+(const CMyString& s1, const CMyString& s2);
	// CMyString& operator+=(const CMyString& other);
	//
	// friend bool operator==(const CMyString& s1, const CMyString& s2);
	// friend bool operator!=(const CMyString& s1, const CMyString& s2);
	//
	// friend bool operator<(const CMyString& s1, const CMyString& s2);
	// friend bool operator>(const CMyString& s1, const CMyString& s2);
	//
	// friend bool operator<=(const CMyString& s1, const CMyString& s2);
	// friend bool operator>=(const CMyString& s1, const CMyString& s2);
	//
	// char const& operator[](size_t index) const;
	// char& operator[](size_t index);
	//
	// friend std::ostream& operator<<(std::ostream& stream, const CMyString& s);
	// friend std::istream& operator>>(std::istream& stream, const CMyString& s);

private:
	char* m_data;
	size_t m_length;
};
