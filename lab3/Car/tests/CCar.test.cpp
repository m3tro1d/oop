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
				REQUIRE(car.GetDirection() == Direction::Still);
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
	}
}
