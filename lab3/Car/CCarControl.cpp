#include "CCarControl.h"

void CCarControl::StartControl(std::istream& input, std::ostream& output)
{
	Command command;
	bool finished = false;

	while (!finished)
	{
		command = ReadCommand(input, output);
		switch (command)
		{
		case Command::HELP:
			PrintHelp(output);
			break;
		case Command::INFO:
			PrintInfo(output);
			break;
		case Command::EXIT:
			finished = true;
			break;
		case Command::ENGINE_ON:
			EngineOn(output);
			break;
		case Command::ENGINE_OFF:
			EngineOff(output);
			break;
		case Command::SET_GEAR:
			SetGear(output);
			break;
		case Command::SET_SPEED:
			SetSpeed(output);
			break;
		default:
			break;
		}
	}
}

CCarControl::Command CCarControl::ReadCommand(std::istream& input, std::ostream& output)
{
	std::string userInput;
	std::getline(input, userInput);

	Command command = Command::IDLE;
	try
	{
		command = ParseCommand(userInput);
	}
	catch (const std::exception& e)
	{
		output << e.what() << '\n';
	}

	return command;
}

CCarControl::Command CCarControl::ParseCommand(const std::string& command)
{
	if (command == "Help")
	{
		return Command::HELP;
	}
	else if (command == "Info")
	{
		return Command::INFO;
	}
	else if (command == "Exit")
	{
		return Command::EXIT;
	}
	else if (command == "EngineOn")
	{
		return Command::ENGINE_ON;
	}
	else if (command == "EngineOff")
	{
		return Command::ENGINE_OFF;
	}
	else if (command == "SetGear")
	{
		return Command::SET_GEAR;
	}
	else if (command == "SetSpeed")
	{
		return Command::SET_SPEED;
	}

	throw std::invalid_argument("invalid command");
}

void PrintHelp(std::ostream& output)
{
}

void PrintInfo(std::ostream& output)
{
}

void EngineOn(std::ostream& output)
{
}

void EngineOff(std::ostream& output)
{
}

void SetGear(std::ostream& output)
{
}

void SetSpeed(std::ostream& output)
{
}
