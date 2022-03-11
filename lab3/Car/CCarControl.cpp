#include "CCarControl.h"

CCarControl::CCarControl(std::istream& input, std::ostream& output, CCar& car)
	: m_input(input)
	, m_output(output)
	, m_car(car)
{
}

void CCarControl::StartControl()
{
	bool finished = false;

	while (!finished)
	{
		m_output << PROMPT;
		auto const command = ReadCommand();
		switch (command.type)
		{
		case CommandType::HELP:
		case CommandType::INFO:
		case CommandType::ENGINE_ON:
		case CommandType::ENGINE_OFF:
		case CommandType::SET_GEAR:
		case CommandType::SET_SPEED:
			GetHandlerForCommand(command.type)(command.argument);
			break;
		case CommandType::EXIT:
			finished = true;
			m_output << "Farewell!\n";
			break;
		default:
			break;
		}
	}
}

CCarControl::Command CCarControl::ReadCommand()
{
	std::string userInput;
	int argument;
	std::getline(m_input, userInput);
	std::stringstream input(userInput);

	CommandType type = CommandType::IDLE;
	std::string commandTypeStr;
	try
	{
		std::getline(input, commandTypeStr, ' ');
		if (!(input >> argument))
		{
			argument = 0;
		}
		type = ParseCommandType(commandTypeStr);
	}
	catch (const std::exception& e)
	{
		m_output << "Error: " << e.what() << '\n';
	}

	return {
		.type = type,
		.argument = argument,
	};
}

CCarControl::CommandType CCarControl::ParseCommandType(const std::string& command)
{
	if (command == "Help")
	{
		return CommandType::HELP;
	}
	else if (command == "Info")
	{
		return CommandType::INFO;
	}
	else if (command == "Exit")
	{
		return CommandType::EXIT;
	}
	else if (command == "EngineOn")
	{
		return CommandType::ENGINE_ON;
	}
	else if (command == "EngineOff")
	{
		return CommandType::ENGINE_OFF;
	}
	else if (command == "SetGear")
	{
		return CommandType::SET_GEAR;
	}
	else if (command == "SetSpeed")
	{
		return CommandType::SET_SPEED;
	}

	throw std::invalid_argument("invalid command");
}

CCarControl::CommandHandler CCarControl::GetHandlerForCommand(CCarControl::CommandType command)
{
	switch (command)
	{
	case CommandType::HELP:
		return [this](int) {
			PrintHelp();
		};
	case CommandType::INFO:
		return [this](int) {
			PrintInfo();
		};
	case CommandType::ENGINE_ON:
		return [this](int) {
			EngineOn();
		};
	case CommandType::ENGINE_OFF:
		return [this](int) {
			EngineOff();
		};
	case CommandType::SET_GEAR:
		return [this](int gear) {
			SetGear(gear);
		};
	case CommandType::SET_SPEED:
		return [this](int speed) {
			SetSpeed(speed);
		};
	default:
		throw std::invalid_argument("no handler for command");
	}
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

void CCarControl::SetGear(int gear)
{
	if (m_car.SetGear(gear))
	{
		m_output << "Gear set to " << gear << '\n';
		return;
	}

	m_output << "Error: can't set gear to " << gear << '\n';
}

void CCarControl::SetSpeed(int speed)
{
	if (m_car.SetSpeed(speed))
	{
		m_output << "Speed set to " << speed << '\n';
		return;
	}

	m_output << "Error: can't set speed to " << speed << '\n';
}

std::string CCarControl::DirectionToString(CCar::Direction direction)
{
	switch (direction)
	{
	case CCar::Direction::FORWARD:
		return "forward";
	case CCar::Direction::STILL:
		return "standing still";
	case CCar::Direction::BACKWARD:
		return "backward";
	default:
		return {};
	}
}
