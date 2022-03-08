#include "CCalculatorControl.h"

int main()
{
	CCalculator calculator;
	CCalculatorControl control(std::cin, std::cout, calculator);
	control.StartControl();

	return EXIT_SUCCESS;
}
