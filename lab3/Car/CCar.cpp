#include "CCar.h"

static constexpr int MIN_GEAR = -1;
static constexpr int MAX_GEAR = 5;

struct SpeedLimits
{
	int lower;
	int upper;
};

const std::map<int, SpeedLimits> GEAR_SPEED_LIMITS = {
	{ -1, { 0, 20 } },
	{ 0, { 0, 150 } },
	{ 1, { 0, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ 5, { 50, 150 } },
};

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

	if (m_speed > 0 && gear == -1 || m_speed < 0 && gear > 0)
	{
		return false;
	}

	auto const limits = GEAR_SPEED_LIMITS.at(gear);
	if (std::abs(m_speed) < limits.lower || std::abs(m_speed) > limits.upper)
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

	if (m_speed < 0)
	{
		m_speed = -speed;
		return true;
	}

	m_speed = m_gear == -1 ? -speed : speed;
	return true;
}

bool CCar::IsTurnedOn() const
{
	return m_isEngineOn;
}

CCar::Direction CCar::GetDirection() const
{
	if (m_speed > 0)
	{
		return Direction::FORWARD;
	}
	else if (m_speed == 0)
	{
		return Direction::STILL;
	}
	else // m_speed < 0
	{
		return Direction::BACKWARD;
	}
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return std::abs(m_speed);
}
