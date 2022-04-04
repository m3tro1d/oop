#pragma once

#include <cstring>
#include <iostream>
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

	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other) noexcept;

	~CMyString() noexcept;

	char const* GetStringData() const;
	size_t GetLength() const;

	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	void Clear();

	// CMyString& operator+=(const CMyString& other);

	char const& operator[](size_t index) const;
	char& operator[](size_t index);

private:
	char* m_data;
	size_t m_length;
};

// TODO
// CMyString const operator+(const CMyString& s1, const CMyString& s2);
//
// bool operator==(const CMyString& s1, const CMyString& s2);
// bool operator!=(const CMyString& s1, const CMyString& s2);
//
// bool operator<(const CMyString& s1, const CMyString& s2);
// bool operator>(const CMyString& s1, const CMyString& s2);
//
// bool operator<=(const CMyString& s1, const CMyString& s2);
// bool operator>=(const CMyString& s1, const CMyString& s2);

std::ostream& operator<<(std::ostream& stream, const CMyString& s);
std::istream& operator>>(std::istream& stream, const CMyString& s);
