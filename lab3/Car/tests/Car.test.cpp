#define CATCH_CONFIG_MAIN
#include "../CCar.h"
#include "../CCarControl.h"
#include "catch.hpp"
#include <sstream>

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
				REQUIRE(car.GetDirection() == CCar::Direction::STILL);
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
					REQUIRE(car.GetDirection() == CCar::Direction::STILL);
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
							REQUIRE(car.GetDirection() == CCar::Direction::BACKWARD);
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
								REQUIRE(car.GetDirection() == CCar::Direction::BACKWARD);
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
								REQUIRE(car.GetDirection() == CCar::Direction::BACKWARD);
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
							REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
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
								REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
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

				WHEN("second gear is set")
				{
					car.SetGear(1);
					car.SetSpeed(20);
					car.SetGear(2);

					THEN("speed from 20 to 50 can be set")
					{
						REQUIRE(car.SetSpeed(20));
						REQUIRE(car.GetSpeed() == 20);
						REQUIRE(car.SetSpeed(50));
						REQUIRE(car.GetSpeed() == 50);
					}

					THEN("speed exceeding limit can't be set")
					{
						REQUIRE(!car.SetSpeed(19));
						REQUIRE(car.GetSpeed() == 20);
						REQUIRE(!car.SetSpeed(51));
						REQUIRE(car.GetSpeed() == 20);
					}
				}

				WHEN("third gear is set")
				{
					car.SetGear(1);
					car.SetSpeed(20);
					car.SetGear(2);
					car.SetSpeed(30);
					car.SetGear(3);

					THEN("speed from 30 to 60 can be set")
					{
						REQUIRE(car.SetSpeed(30));
						REQUIRE(car.GetSpeed() == 30);
						REQUIRE(car.SetSpeed(60));
						REQUIRE(car.GetSpeed() == 60);
					}

					THEN("speed exceeding limit can't be set")
					{
						REQUIRE(!car.SetSpeed(29));
						REQUIRE(car.GetSpeed() == 30);
						REQUIRE(!car.SetSpeed(61));
						REQUIRE(car.GetSpeed() == 30);
					}
				}

				WHEN("fourth gear is set")
				{
					car.SetGear(1);
					car.SetSpeed(20);
					car.SetGear(2);
					car.SetSpeed(30);
					car.SetGear(3);
					car.SetSpeed(40);
					car.SetGear(4);

					THEN("speed from 40 to 90 can be set")
					{
						REQUIRE(car.SetSpeed(40));
						REQUIRE(car.GetSpeed() == 40);
						REQUIRE(car.SetSpeed(90));
						REQUIRE(car.GetSpeed() == 90);
					}

					THEN("speed exceeding limit can't be set")
					{
						REQUIRE(!car.SetSpeed(39));
						REQUIRE(car.GetSpeed() == 40);
						REQUIRE(!car.SetSpeed(91));
						REQUIRE(car.GetSpeed() == 40);
					}
				}

				WHEN("fifth gear is set")
				{
					car.SetGear(1);
					car.SetSpeed(20);
					car.SetGear(2);
					car.SetSpeed(30);
					car.SetGear(3);
					car.SetSpeed(40);
					car.SetGear(4);
					car.SetSpeed(50);
					car.SetGear(5);

					THEN("speed from 50 to 150 can be set")
					{
						REQUIRE(car.SetSpeed(50));
						REQUIRE(car.GetSpeed() == 50);
						REQUIRE(car.SetSpeed(150));
						REQUIRE(car.GetSpeed() == 150);
					}

					THEN("speed exceeding limit can't be set")
					{
						REQUIRE(!car.SetSpeed(49));
						REQUIRE(car.GetSpeed() == 50);
						REQUIRE(!car.SetSpeed(151));
						REQUIRE(car.GetSpeed() == 50);
					}
				}
			}
		}
	}
}

TEST_CASE("car control works correctly")
{
	CCar car;
	std::istringstream input;
	std::ostringstream output;
	CCarControl control(input, output, car);

	SECTION("printing help works correctly")
	{
		input.str("Help\nExit\n");
		const std::string result = "> Help             show this message\n"
								   "Info             print car info\n"
								   "Exit             stop the program\n"
								   "EngineOn         start the car engine\n"
								   "EngineOff        stop the car engine\n"
								   "SetGear <gear>   change car gear\n"
								   "SetSpeed <speed> change car speed\n"
								   "> Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
	}

	SECTION("printing info works correctly")
	{
		SECTION("newly created car info is printed correctly")
		{
			input.str("Info\nExit\n");
			const std::string result = "> Car state:\n"
									   "Engine: off\n"
									   "Direction: standing still\n"
									   "Speed: 0\n"
									   "Gear: 0\n"
									   "> Farewell!\n";
			control.StartControl();
			REQUIRE(output.str() == result);
		}

		SECTION("modified car info is printed correctly")
		{
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(15);
			input.str("Info\nExit\n");
			const std::string result = "> Car state:\n"
									   "Engine: on\n"
									   "Direction: forward\n"
									   "Speed: 15\n"
									   "Gear: 1\n"
									   "> Farewell!\n";
			control.StartControl();
			REQUIRE(output.str() == result);
		}
	}

	SECTION("turning engine on works correctly")
	{
		input.str("EngineOn\nExit\n");
		const std::string result = "> Engine turned on\n"
								   "> Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
		REQUIRE(car.IsTurnedOn());
	}

	SECTION("turning engine off works correctly")
	{
		input.str("EngineOn\nEngineOff\nExit\n");
		const std::string result = "> Engine turned on\n"
								   "> Engine turned off\n"
								   "> Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
		REQUIRE(!car.IsTurnedOn());
	}

	SECTION("setting gear works correctly")
	{
		input.str("EngineOn\nSetGear 1\nExit\n");
		const std::string result = "> Engine turned on\n"
								   "> Gear set to 1\n"
								   "> Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
		REQUIRE(car.GetGear() == 1);
	}

	SECTION("setting speed works correctly")
	{
		input.str("EngineOn\nSetGear 1\nSetSpeed 20\nExit\n");
		const std::string result = "> Engine turned on\n"
								   "> Gear set to 1\n"
								   "> Speed set to 20\n"
								   "> Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
		REQUIRE(car.GetSpeed() == 20);
	}

	SECTION("invalid command results in an error")
	{
		input.str("EngineOff\nExit\n");
		const std::string result = "> Error: can't turn off the engine\n"
								   "> Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
		REQUIRE(!car.IsTurnedOn());
	}

	SECTION("unknown command results in an error")
	{
		input.str("BrewMeACoffee\nExit\n");
		const std::string result = "> Error: invalid command\n"
								   "> Farewell!\n";
		control.StartControl();
		REQUIRE(output.str() == result);
	}
}
