#pragma once

#include "CCar.h"

class CCarControl
{
public:
	void StartControl(std::istream& input, std::ostream& output);

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

	static CCarControl::Command ReadCommand(std::istream& input, std::ostream& output);
	static CCarControl::Command ParseCommand(const std::string& command);

	void PrintHelp(std::ostream& output);
	void PrintInfo(std::ostream& output);
	void EngineOn(std::ostream& output);
	void EngineOff(std::ostream& output);
	void SetGear(std::ostream& output);
	void SetSpeed(std::ostream& output);

	CCar m_car;
};
