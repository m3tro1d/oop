#include "CCarControl.h"

CCarControl::CCarControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CCarControl::StartControl()
{
	Command command;
	bool finished = false;

	while (!finished)
	{
		m_output << "> ";
		command = ReadCommand();
		switch (command)
		{
		case Command::HELP:
			PrintHelp();
			break;
		case Command::INFO:
			PrintInfo();
			break;
		case Command::EXIT:
			finished = true;
			m_output << "Farewell!\n";
			break;
		case Command::ENGINE_ON:
			EngineOn();
			break;
		case Command::ENGINE_OFF:
			EngineOff();
			break;
		case Command::SET_GEAR:
			SetGear();
			break;
		case Command::SET_SPEED:
			SetSpeed();
			break;
		default:
			break;
		}
	}
}

CCarControl::Command CCarControl::ReadCommand()
{
	std::string userInput;
	std::getline(m_input, userInput);

	Command command = Command::IDLE;
	try
	{
		command = ParseCommand(userInput);
	}
	catch (const std::exception& e)
	{
		m_output << "Error: " << e.what() << '\n';
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

void CCarControl::PrintHelp()
{
	m_output << "Help             show this message\n"
				"Info             print car info\n"
				"Exit             stop the program\n"
				"EngineOn         start the car engine\n"
				"EngineOff        stop the car engine\n"
				"SetGear <gear>   change car gear\n"
				"SetSpeed <speed> change car speed\n";
}

void CCarControl::PrintInfo()
{
	m_output << "Car state:\n"
			 << "Engine: " << (m_car.IsTurnedOn() ? "on" : "off") << '\n'
			 << "Direction: " << DirectionToString(m_car.GetDirection()) << '\n'
			 << "Speed: " << m_car.GetSpeed() << '\n'
			 << "Gear: " << m_car.GetGear() << '\n';
}

void CCarControl::EngineOn()
{
	if (m_car.TurnOnEngine())
	{
		m_output << "Engine turned on\n";
		return;
	}

	m_output << "Error: can't turn on the engine\n";
}

void CCarControl::EngineOff()
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Engine turned off\n";
		return;
	}

	m_output << "Error: can't turn off the engine\n";
}

void CCarControl::SetGear()
{
}

void CCarControl::SetSpeed()
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
