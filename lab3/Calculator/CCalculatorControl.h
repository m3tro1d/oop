#pragma once

#include "CCalculator.h"
#include <iostream>

class CCalculatorControl
{
public:
	CCalculatorControl(std::istream& input, std::ostream& output, CCalculator& calculator);
	void StartControl();

private:
	std::istream& m_input;
	std::ostream& m_output;
	CCalculator& m_calculator;
};
