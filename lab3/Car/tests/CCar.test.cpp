#define CATCH_CONFIG_MAIN
#include "../CCar.h"
#include "catch.hpp"

SCENARIO("car is operated correctly")
{
	GIVEN("a car")
	{
		CCar car;

		WHEN("it is just created")
		{
			THEN("the engine is off")
			{
				REQUIRE(!car.IsTurnedOn());
			}

			THEN("it is at zeroth gear")
			{
				REQUIRE(car.GetGear() == 0);
			}

			THEN("it has zero speed")
			{
				REQUIRE(car.GetSpeed() == 0);
			}

			THEN("it is not moving")
			{
				REQUIRE(car.GetDirection() == Direction::STILL);
			}

			THEN("it can't change gear")
			{
				REQUIRE(!car.SetGear(1));
				REQUIRE(car.GetGear() == 0);
			}

			THEN("it can't change speed")
			{
				REQUIRE(!car.SetSpeed(10));
				REQUIRE(car.GetSpeed() == 0);
			}

			THEN("the engine can't be turned off")
			{
				REQUIRE(!car.TurnOffEngine());
				REQUIRE(!car.IsTurnedOn());
			}

			THEN("the engine can be turned on")
			{
				REQUIRE(car.TurnOnEngine());
				REQUIRE(car.IsTurnedOn());
			}
		}

		WHEN("the engine is turned on")
		{
			car.TurnOnEngine();

			THEN("it is at zeroth gear")
			{
				REQUIRE(car.GetGear() == 0);
			}

			THEN("it has zero speed")
			{
				REQUIRE(car.GetSpeed() == 0);
			}

			THEN("it is not moving")
			{
				REQUIRE(car.GetDirection() == Direction::STILL);
			}

			THEN("the engine can be turned off")
			{
				REQUIRE(car.TurnOffEngine());
				REQUIRE(!car.IsTurnedOn());
			}

			THEN("the engine can't be turned on")
			{
				REQUIRE(!car.TurnOnEngine());
				REQUIRE(car.IsTurnedOn());
			}

			THEN("it can set first gear")
			{
				REQUIRE(car.SetGear(1));
				REQUIRE(car.GetGear() == 1);
			}

			THEN("it can set reverse gear")
			{
				REQUIRE(car.SetGear(-1));
				REQUIRE(car.GetGear() == -1);
			}
		}

		WHEN("it is turned on and first gear is set")
		{
			car.TurnOnEngine();
			car.SetGear(1);

			THEN("the engine can't be turned off")
			{
				REQUIRE(!car.TurnOffEngine());
				REQUIRE(car.IsTurnedOn());
			}

			THEN("speed from 0 to 30 can be set")
			{
				REQUIRE(car.SetSpeed(30));
				REQUIRE(car.GetSpeed() == 30);
				REQUIRE(car.SetSpeed(0));
				REQUIRE(car.GetSpeed() == 0);
			}

			THEN("speed exceeding limit can't be set")
			{
				REQUIRE(!car.SetSpeed(31));
				REQUIRE(car.GetSpeed() == 0);
			}

			THEN("setting speed more than 0 makes car move forward")
			{
				REQUIRE(car.SetSpeed(20));
				REQUIRE(car.GetDirection() == Direction::FORWARD);
			}

			THEN("second gear can't be set if the speed is not enough")
			{
				REQUIRE(car.SetSpeed(10));
				REQUIRE(!car.SetGear(2));
				REQUIRE(car.GetGear() == 1);
			}

			THEN("second gear can be set if the speed is enough")
			{
				REQUIRE(car.SetSpeed(20));
				REQUIRE(car.SetGear(2));
				REQUIRE(car.GetGear() == 2);
			}

			THEN("third gear can be set if the speed is enough")
			{
				REQUIRE(car.SetSpeed(30));
				REQUIRE(car.SetGear(3));
				REQUIRE(car.GetGear() == 3);
			}
		}

		WHEN("it is turned on and reverse gear is set")
		{
			car.TurnOnEngine();
			car.SetGear(-1);

			THEN("the engine can't be turned off")
			{
				REQUIRE(!car.TurnOffEngine());
				REQUIRE(car.IsTurnedOn());
			}

			THEN("speed from 0 to 20 can be set")
			{
				REQUIRE(car.SetSpeed(20));
				REQUIRE(car.GetSpeed() == 20);
				REQUIRE(car.SetSpeed(0));
				REQUIRE(car.GetSpeed() == 0);
			}

			THEN("speed exceeding limit can't be set")
			{
				REQUIRE(!car.SetSpeed(21));
				REQUIRE(car.GetSpeed() == 0);
			}

			THEN("setting speed more than 0 makes car move backward")
			{
				REQUIRE(car.SetSpeed(10));
				REQUIRE(car.GetDirection() == Direction::BACKWARD);
			}
		}
	}
}
