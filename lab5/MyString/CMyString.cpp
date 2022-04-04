#include "CMyString.h"

CMyString::CMyString()
	: m_data(new char[1])
	, m_length(0)
{
	m_data[0] = '\0';
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
	: m_data(new char[length + 1])
	, m_length(length)
{
	std::memcpy(m_data, pString, m_length);
	m_data[m_length] = '\0';
}

CMyString::CMyString(const CMyString& other)
	: CMyString(other.m_data, other.m_length)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_data(other.m_data)
	, m_length(other.m_length)
{
	other.m_data = nullptr;
	other.m_length = 0;
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (std::addressof(other) != this)
	{
		CMyString copy(other);
		std::swap(m_data, copy.m_data);
		std::swap(m_length, copy.m_length);
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (std::addressof(other) != this)
	{
		delete[] m_data;

		m_data = other.m_data;
		m_length = other.m_length;

		other.m_data = nullptr;
		other.m_length = 0;
	}
	return *this;
}

CMyString::~CMyString() noexcept
{
	delete[] m_data;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

char const* CMyString::GetStringData() const
{
	return m_data;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start > m_length)
	{
		throw std::out_of_range("index out of range");
	}

	size_t copyLength = length;
	if (start + length > m_length)
	{
		copyLength = m_length - start;
	}

	return { m_data + start, copyLength };
}

void CMyString::Clear()
{
	std::memset(m_data, '\0', m_length);
	m_length = 0;
}
