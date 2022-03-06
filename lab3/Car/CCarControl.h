#pragma once

#include "CCar.h"
#include <iostream>
#include <string>
#include <sstream>

class CCarControl
{
public:
	CCarControl(std::istream& input, std::ostream& output, CCar& car);
	void StartControl();

private:
	enum class Command
	{
		IDLE,
		HELP,
		INFO,
		EXIT,
		ENGINE_ON,
		ENGINE_OFF,
		SET_GEAR,
		SET_SPEED,
	};

	CCarControl::Command ReadCommand();
	static CCarControl::Command ParseCommand(const std::string& command);

	void PrintHelp();
	void PrintInfo();
	void EngineOn();
	void EngineOff();
	void SetGear();
	void SetSpeed();

	static std::string DirectionToString(Direction direction);

	std::istream& m_input;
	std::ostream& m_output;
	CCar m_car;
	int m_argument = 0; // FIXME: this is a bad approach
};