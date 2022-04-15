#include "CMyString.h"

static constexpr size_t MAX_STRING = 1000;
constexpr char STRING_END = '\0';

CMyString::CMyString()
	: m_data(new char[1])
	, m_length(0)
{
	m_data[0] = STRING_END;
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, pString != nullptr ? std::strlen(pString) : 0)
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (pString == nullptr)
	{
		length = 0;
	}

	m_data = new char[length + 1];
	m_length = length;
	std::memcpy(m_data, pString, m_length);
	m_data[m_length] = STRING_END;
}

CMyString::CMyString(CMyString const& other)
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

CMyString& CMyString::operator=(CMyString const& other)
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
	if (length > m_length - start)
	{
		copyLength = m_length - start;
	}

	return { m_data + start, copyLength };
}

void CMyString::Clear()
{
	m_data[0] = STRING_END;
	m_length = 0;
}

CMyString::iterator CMyString::begin()
{
	return m_data;
}

CMyString::iterator CMyString::end()
{
	return m_data + m_length;
}

CMyString::const_iterator CMyString::begin() const
{
	return m_data;
}

CMyString::const_iterator CMyString::end() const
{
	return m_data + m_length;
}

CMyString::const_iterator CMyString::cbegin() const
{
	return m_data;
}

CMyString::const_iterator CMyString::cend() const
{
	return m_data + m_length;
}

CMyString::reverse_iterator CMyString::rbegin()
{
	return m_data + m_length - 1;
}

CMyString::reverse_iterator CMyString::rend()
{
	return m_data - 1;
}

CMyString::const_reverse_iterator CMyString::crbegin() const
{
	return m_data + m_length - 1;
}

CMyString::const_reverse_iterator CMyString::crend() const
{
	return m_data - 1;
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	size_t resultLength = m_length + other.m_length;
	char* result = new char[resultLength + 1];

	std::memcpy(result, m_data, m_length);
	std::memcpy(result + m_length, other.m_data, other.m_length);
	result[resultLength] = STRING_END;

	delete[] m_data;
	m_data = result;
	m_length = resultLength;

	return *this;
}

char const& CMyString::operator[](size_t index) const
{
	if (index > m_length)
	{
		throw std::out_of_range("index out of range");
	}

	return m_data[index];
}

char& CMyString::operator[](size_t index)
{
	if (index > m_length)
	{
		throw std::out_of_range("index out of range");
	}

	return m_data[index];
}

std::istream& operator>>(std::istream& stream, CMyString& s)
{
	// TODO: no limit
	char* result = new char[MAX_STRING + 1];
	size_t resultLength = 0;
	char ch;

	while (stream.get(ch) && ch != '\n')
	{
		result[resultLength++] = ch;
	}
	result[resultLength] = STRING_END;

	delete[] s.m_data;
	s.m_data = result;
	s.m_length = resultLength;

	return stream;
}

CMyString const operator+(CMyString s1, CMyString const& s2)
{
	return s1 += s2;
}

static int StrCmp(CMyString const& s1, CMyString const& s2)
{
	size_t minLength = std::min(s1.GetLength(), s2.GetLength());
	int result = std::memcmp(s1.GetStringData(), s2.GetStringData(), minLength);

	if (result != 0)
	{
		return result;
	}

	if (s2.GetLength() > minLength)
	{
		return -1;
	}

	if (s1.GetLength() > minLength)
	{
		return 1;
	}

	return result;
}

bool operator==(CMyString const& s1, CMyString const& s2)
{
	return StrCmp(s1, s2) == 0;
}

bool operator!=(CMyString const& s1, CMyString const& s2)
{
	return StrCmp(s1, s2) != 0;
}

bool operator<(CMyString const& s1, CMyString const& s2)
{
	return StrCmp(s1, s2) < 0;
}

bool operator>(CMyString const& s1, CMyString const& s2)
{
	return StrCmp(s1, s2) > 0;
}

bool operator<=(CMyString const& s1, CMyString const& s2)
{
	return StrCmp(s1, s2) <= 0;
}

bool operator>=(CMyString const& s1, CMyString const& s2)
{
	return StrCmp(s1, s2) >= 0;
}

std::ostream& operator<<(std::ostream& stream, CMyString const& s)
{
	for (size_t i = 0; i < s.GetLength(); ++i)
	{
		stream << s.GetStringData()[i];
	}
	return stream;
}
