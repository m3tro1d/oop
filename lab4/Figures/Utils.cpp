#include "Utils.h"

void PrintColor(std::ostream& output, uint32_t color)
{
	output << '#'
		   << std::hex << std::setw(6) << std::setfill('0')
		   << color;
}
