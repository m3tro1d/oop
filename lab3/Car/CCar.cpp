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
	if (!m_isEngineOn || m_gear != 0 || m_speed != 0)
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

	if (gear < MIN_GEAR || gear > MAX_GEAR)
	{
		return false;
	}

	if (m_direction == Direction::FORWARD && gear == -1 || m_direction == Direction::BACKWARD && gear > 0)
	{
		return false;
	}

	auto const limits = GEAR_SPEED_LIMITS.at(gear);
	if (m_speed < limits.lower || m_speed > limits.upper)
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

	if (m_gear == 0 && speed > std::abs(m_speed))
	{
		return false;
	}

	auto const limits = GEAR_SPEED_LIMITS.at(m_gear);
	if (speed < limits.lower || speed > limits.upper)
	{
		return false;
	}

	m_speed = m_gear == -1 ? -speed : speed;
	UpdateDirection();
	return true;
}

bool CCar::IsTurnedOn() const
{
	return m_isEngineOn;
}

CCar::Direction CCar::GetDirection() const
{
	return m_direction;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return std::abs(m_speed);
}

void CCar::UpdateDirection()
{
	if (m_speed > 0)
	{
		m_direction = Direction::FORWARD;
		return;
	}

	if (m_speed < 0)
	{
		m_direction = Direction::BACKWARD;
		return;
	}

	m_direction = Direction::STILL;
}
