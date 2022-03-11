#include "StringLib.h"

void Trim(std::string& string)
{
	string.erase(string.find_last_not_of(' ') + 1);
	string.erase(0, string.find_first_not_of(' '));
}
