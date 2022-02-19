#include "HTMLProcessor.h"

constexpr char PATTERN_START = '&';

const std::unordered_map<std::string, std::string> PATTERNS = {
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" },
};

constexpr size_t LOOKUP_SIZE = 6;

std::string TryFindReplacePattern(const std::string& html, size_t& replacePosition)
{
	auto match = html.substr(replacePosition, LOOKUP_SIZE);
	for (auto const& pattern : PATTERNS)
	{
		if (match.find(pattern.first) == 0)
		{
			replacePosition += pattern.first.length();
			return pattern.second;
		}
	}

	replacePosition += match.length();
	return match;
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
