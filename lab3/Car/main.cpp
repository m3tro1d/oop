#include "CCarControl.h"

int main()
{
	CCarControl control(std::cin, std::cout);
	control.StartControl();

	return EXIT_SUCCESS;
}
