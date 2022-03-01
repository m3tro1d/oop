#include "StringLib.h"

std::string ToLower(const std::string& string)
{
	std::string result;
	std::transform(
		string.begin(),
		string.end(),
		std::back_inserter(result),
		[](char ch) {
			return std::tolower(ch);
		});

	return result;
}

void Trim(std::string& string)
{
	string.erase(string.find_last_not_of(' ') + 1);
	string.erase(0, string.find_first_not_of(' '));
}

std::set<std::string> StringToSet(const std::string& string, char delimiter)
{
	std::stringstream ss(string);
	std::string part;
	std::set<std::string> result;

	while (std::getline(ss, part, delimiter))
	{
		Trim(part);
		if (!part.empty())
		{
			result.insert(part);
		}
	}

	return result;
}

std::string SetToString(const std::set<std::string>& set, const std::string& delimiter)
{
	std::string result;
	auto last = set.end();
	--last;
	for (auto it = set.begin(); it != set.end(); ++it)
	{
		result.append(*it);
		if (it != last)
		{
			result.append(delimiter);
		}
	}

	return result;
}
