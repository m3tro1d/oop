#pragma once

#include <iostream>

enum class Direction
{
	Forward,
	Still,
	Backward,
};

class CCar
{
public:
	static constexpr int MIN_GEAR = -1;
	static constexpr int MAX_GEAR = 5;

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
