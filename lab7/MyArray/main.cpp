#include "CMyArray.hpp"
#include <iostream>
#include <string>

int main()
{
	CMyArray<int> intArray;
	intArray.Push(1);
	intArray.Push(2);
	intArray.Push(3);
	for (auto const& element : intArray)
	{
		std::cout << element << '\n';
	}

	CMyArray<std::string> stringArray;
	stringArray.Push("Bitterness and burden");
	stringArray.Push("Curses rest on thee");
	stringArray.Push("Solitaire and sorrow");
	for (auto const& element : stringArray)
	{
		std::cout << element << '\n';
	}

	return EXIT_SUCCESS;
}
