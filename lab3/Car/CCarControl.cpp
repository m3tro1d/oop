#include "CCarControl.h"

void CCarControl::StartControl(std::istream& input, std::ostream& output)
{
	Command command;
	bool finished = false;

	while (!finished)
	{
		output << "> ";
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
			output << "Farewell!\n";
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
		output << "Error: " << e.what() << '\n';
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

void CCarControl::PrintHelp(std::ostream& output)
{
	output << "Help             show this message\n"
			  "Info             print car info\n"
			  "Exit             stop the program\n"
			  "EngineOn         start the car engine\n"
			  "EngineOff        stop the car engine\n"
			  "SetGear <gear>   change car gear\n"
			  "SetSpeed <speed> change car speed\n";
}

void CCarControl::PrintInfo(std::ostream& output)
{
	output << "Car state:\n"
		   << "Engine: " << (m_car.IsTurnedOn() ? "on" : "off") << '\n'
		   << "Direction: " << DirectionToString(m_car.GetDirection()) << '\n'
		   << "Speed: " << m_car.GetSpeed() << '\n'
		   << "Gear: " << m_car.GetGear() << '\n';
}

void CCarControl::EngineOn(std::ostream& output)
{
	if (m_car.TurnOnEngine())
	{
		output << "Engine turned on\n";
		return;
	}

	output << "Error: can't turn on the engine\n";
}

void CCarControl::EngineOff(std::ostream& output)
{
	if (m_car.TurnOffEngine())
	{
		output << "Engine turned off\n";
		return;
	}

	output << "Error: can't turn off the engine\n";
}

void CCarControl::SetGear(std::ostream& output)
{
}

void CCarControl::SetSpeed(std::ostream& output)
{
}

std::string CCarControl::DirectionToString(Direction direction)
{
	switch (direction)
	{
	case Direction::FORWARD:
		return "forward";
	case Direction::STILL:
		return "standing still";
	case Direction::BACKWARD:
		return "backward";
	default:
		return {};
	}
}
