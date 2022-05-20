#include "CMyArray.hpp"
#include <iostream>
#include <string>

int main()
{
	CMyArray<std::string> arrayOfStrings;
	arrayOfStrings.Push("Bitterness and burden");
	arrayOfStrings.Push("Curses rest on thee");
	arrayOfStrings.Push("Solitaire and sorrow");
	std::copy(
		arrayOfStrings.begin(),
		arrayOfStrings.end(),
		std::ostream_iterator<std::string>(std::cout, "\n"));
	std::cout << '\n';

	CMyArray<double> arrayOfDoubles;
	arrayOfDoubles.Push(1337.42);
	arrayOfDoubles.Push(12);
	arrayOfDoubles.Push(135.99);
	std::copy(
		arrayOfDoubles.begin(),
		arrayOfDoubles.end(),
		std::ostream_iterator<double>(std::cout, "\n"));

	return EXIT_SUCCESS;
}
