#include "CMyString.h"

static constexpr size_t MAX_STRING = 1000;

CMyString::CMyString()
	: m_data(new char[1])
	, m_length(0)
{
	m_data[0] = '\0';
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
	m_data[m_length] = '\0';
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
	std::memset(m_data, '\0', m_length);
	m_length = 0;
}

CMyString::Iterator CMyString::begin()
{
	return Iterator(m_data);
}

CMyString::Iterator CMyString::end()
{
	return Iterator(m_data + m_length);
}

CMyString::ConstIterator CMyString::cbegin() const
{
	return ConstIterator(m_data);
}

CMyString::ConstIterator CMyString::cend() const
{
	return ConstIterator(m_data + m_length);
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	size_t resultLength = m_length + other.m_length;
	char* result = new char[resultLength + 1];

	std::memcpy(result, m_data, m_length);
	std::memcpy(result + m_length, other.m_data, other.m_length);
	result[resultLength] = '\0';

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
	char* result = new char[MAX_STRING + 1];
	size_t resultLength = 0;
	char ch;

	while (stream.get(ch) && ch != '\n')
	{
		result[resultLength++] = ch;
	}
	result[resultLength] = '\0';

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

CMyString::Iterator::Iterator(CMyString::Iterator::PointerType ptr)
	: m_ptr(ptr)
{
}

CMyString::Iterator& CMyString::Iterator::operator++()
{
	++m_ptr;
	return *this;
}

CMyString::Iterator const CMyString::Iterator::operator++(int)
{
	Iterator iterator = *this;
	++(*this);
	return iterator;
}

CMyString::Iterator::PointerType CMyString::Iterator::operator->() const
{
	return m_ptr;
}

CMyString::Iterator::ValueType& CMyString::Iterator::operator*() const
{
	return *m_ptr;
}

CMyString::Iterator::ReferenceType CMyString::Iterator::operator[](size_t index) const
{
	return *(m_ptr + index);
}

bool CMyString::Iterator::operator==(const CMyString::Iterator& other) const
{
	return m_ptr == other.m_ptr;
}

bool CMyString::Iterator::operator!=(const CMyString::Iterator& other) const
{
	return !(*this == other);
}

CMyString::ConstIterator::ConstIterator(CMyString::ConstIterator::PointerType ptr)
	: m_ptr(ptr)
{
}

CMyString::ConstIterator& CMyString::ConstIterator::operator++()
{
	++m_ptr;
	return *this;
}

CMyString::ConstIterator const CMyString::ConstIterator::operator++(int)
{
	ConstIterator iterator = *this;
	++(*this);
	return iterator;
}

CMyString::ConstIterator::PointerType CMyString::ConstIterator::operator->() const
{
	return m_ptr;
}

CMyString::ConstIterator::ValueType& CMyString::ConstIterator::operator*() const
{
	return *m_ptr;
}

CMyString::ConstIterator::ReferenceType CMyString::ConstIterator::operator[](size_t index) const
{
	return *(m_ptr + index);
}

bool CMyString::ConstIterator::operator==(const CMyString::ConstIterator& other) const
{
	return m_ptr == other.m_ptr;
}

bool CMyString::ConstIterator::operator!=(const CMyString::ConstIterator& other) const
{
	return !(*this == other);
}
