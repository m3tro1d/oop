#pragma once

#include <iostream>
#include <map>

class CCar
{
public:
	enum class Direction
	{
		FORWARD,
		STILL,
		BACKWARD,
	};

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
	void UpdateDirection();

	static constexpr int MIN_GEAR = -1;
	static constexpr int MAX_GEAR = 5;

	struct SpeedLimits
	{
		int lower;
		int upper;
	};

	const std::map<int, SpeedLimits> GEAR_SPEED_LIMITS = {
		{ -1, { 0, 20 } },
		{ 0, { -20, 150 } },
		{ 1, { 0, 30 } },
		{ 2, { 20, 50 } },
		{ 3, { 30, 60 } },
		{ 4, { 40, 90 } },
		{ 5, { 50, 150 } },
	};

	bool m_isEngineOn = false;
	int m_gear = 0;
	int m_speed = 0;
	Direction m_direction = Direction::STILL;
};
