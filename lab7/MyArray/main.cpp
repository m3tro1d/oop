#include "CMyArray.hpp"
#include <iostream>
#include <string>

int main()
{
	CMyArray<std::string> arrayOfStrings;
	arrayOfStrings.Push("Bitterness and burden");
	arrayOfStrings.Push("Curses rest on thee");
	arrayOfStrings.Push("Solitaire and sorrow");
	for (auto const& element : arrayOfStrings)
	{
		std::cout << element << '\n';
	}

	CMyArray<double> arrayOfDoubles;
	arrayOfDoubles.Push(1337.42);
	arrayOfDoubles.Push(12);
	arrayOfDoubles.Push(135.99);
	for (auto const& element : arrayOfDoubles)
	{
		std::cout << element << '\n';
	}

	return EXIT_SUCCESS;
}
