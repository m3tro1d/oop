#include "HTMLProcessor.h"

constexpr char PATTERN_START = '&';

using PatternDictionary = std::vector<std::pair<std::string, std::string>>;

const PatternDictionary PATTERNS = {
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" },
};

std::string TryFindReplacePattern(const std::string& html, size_t& replacePosition)
{
	for (auto const& [pattern, replacement] : PATTERNS)
	{
		if (html.compare(replacePosition, pattern.length(), pattern) == 0)
		{
			replacePosition += pattern.length();
			return replacement;
		}
	}

	++replacePosition;
	return { PATTERN_START };
}

std::string HtmlDecode(const std::string& html)
{
	size_t searchPosition = 0;
	std::string result;
	while (searchPosition < html.length())
	{
		size_t replacePosition = html.find(PATTERN_START, searchPosition);
		result.append(html, searchPosition, replacePosition - searchPosition);

		if (replacePosition == std::string::npos)
		{
			break;
		}

		auto const pattern = TryFindReplacePattern(html, replacePosition);
		result.append(pattern);
		searchPosition = replacePosition;
	}

	return result;
}

void HtmlDecode(std::istream& input, std::ostream& output)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << HtmlDecode(line) << '\n';
	}
}
