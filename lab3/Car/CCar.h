#pragma once

#include <array>
#include <iostream>

enum class Direction
{
	FORWARD,
	STILL,
	BACKWARD,
};

constexpr int MIN_GEAR = -1;
constexpr int MAX_GEAR = 5;

// TODO: limit gear speed ranges

class CCar
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetGear() const;
	int GetSpeed() const;

private:
	bool m_isEngineOn = false;
	int m_gear = 0;
	int m_speed = 0;
};
