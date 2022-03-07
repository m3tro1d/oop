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
				REQUIRE(!car.SetGear(-1));
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

				THEN("neutral gear can be set")
				{
					REQUIRE(car.SetGear(0));
					REQUIRE(car.GetGear() == 0);
				}

				WHEN("reverse gear is set")
				{
					car.SetGear(-1);

					THEN("the engine can't be turned off")
					{
						REQUIRE(!car.TurnOffEngine());
						REQUIRE(car.IsTurnedOn());
					}

					THEN("neutral gear can be set")
					{
						REQUIRE(car.SetGear(0));
						REQUIRE(car.GetGear() == 0);
					}

					THEN("reverse gear can be set")
					{
						REQUIRE(car.SetGear(-1));
						REQUIRE(car.GetGear() == -1);
					}

					THEN("first gear can be set")
					{
						REQUIRE(car.SetGear(1));
						REQUIRE(car.GetGear() == 1);
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

					WHEN("it speeds up")
					{
						car.SetSpeed(10);

						THEN("it is moving backward")
						{
							REQUIRE(car.GetDirection() == Direction::BACKWARD);
						}

						THEN("first gear can't be set")
						{
							REQUIRE(!car.SetGear(1));
							REQUIRE(car.GetGear() == -1);
						}

						THEN("neutral gear can be set")
						{
							REQUIRE(car.SetGear(0));
							REQUIRE(car.GetGear() == 0);
						}

						WHEN("neutral gear is set")
						{
							car.SetGear(0);

							THEN("it has the same speed")
							{
								REQUIRE(car.GetSpeed() == 10);
							}

							THEN("it is still moving backwards")
							{
								REQUIRE(car.GetDirection() == Direction::BACKWARD);
							}

							THEN("it can't speed up")
							{
								REQUIRE(!car.SetSpeed(15));
								REQUIRE(car.GetSpeed() == 10);
							}

							THEN("it can slow down")
							{
								REQUIRE(car.SetSpeed(5));
								REQUIRE(car.GetSpeed() == 5);
							}
						}
					}
				}

				WHEN("first gear is set")
				{
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
						REQUIRE(!car.SetSpeed(-10));
						REQUIRE(car.GetSpeed() == 0);
					}

					THEN("fist gear can be set")
					{
						REQUIRE(car.SetGear(1));
						REQUIRE(car.GetGear() == 1);
					}

					WHEN("it speeds up")
					{
						car.SetSpeed(20);

						THEN("it is moving forward")
						{
							REQUIRE(car.GetDirection() == Direction::FORWARD);
						}

						THEN("reverse gear can't be set")
						{
							REQUIRE(!car.SetGear(-1));
							REQUIRE(car.GetGear() == 1);
						}

						THEN("neutral gear can be set")
						{
							REQUIRE(car.SetGear(0));
							REQUIRE(car.GetGear() == 0);
						}

						WHEN("neutral gear is set")
						{
							car.SetGear(0);

							THEN("it has the same speed")
							{
								REQUIRE(car.GetSpeed() == 20);
							}

							THEN("it is still moving forward")
							{
								REQUIRE(car.GetDirection() == Direction::FORWARD);
							}

							THEN("it can't speed up")
							{
								REQUIRE(!car.SetSpeed(25));
								REQUIRE(car.GetSpeed() == 20);
							}

							THEN("it can slow down")
							{
								REQUIRE(car.SetSpeed(10));
								REQUIRE(car.GetSpeed() == 10);
							}
						}
					}
				}
			}
		}
	}
}
