#include "CCarControl.h"

int main()
{
	CCar car;
	CCarControl control(std::cin, std::cout, car);
	control.StartControl();

	return EXIT_SUCCESS;
}
