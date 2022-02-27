#include "CCar.h"

bool CCar::TurnOnEngine()
{
	if (m_isEngineOn)
	{
		return false;
	}

	m_isEngineOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (!m_isEngineOn)
	{
		return false;
	}

	m_isEngineOn = false;
	return true;
}

bool CCar::SetGear(int gear)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	m_gear = gear;
	return true;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	m_speed = speed;
	return true;
}

bool CCar::IsTurnedOn() const
{
	return m_isEngineOn;
}

Direction CCar::GetDirection() const
{
	return Direction::Still;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}
