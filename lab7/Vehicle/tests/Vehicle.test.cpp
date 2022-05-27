#define CATCH_CONFIG_MAIN
#include "../People/CPerson.h"
#include "../People/CPoliceMan.h"
#include "../People/CRacer.h"
#include "../Vehicles/CBus.h"
#include "../Vehicles/Cars/CPoliceCar.h"
#include "../Vehicles/Cars/CRacingCar.h"
#include "../Vehicles/Cars/CTaxi.h"
#include "catch.hpp"

SCENARIO("creating a person")
{
	GIVEN("a name")
	{
		std::string const name = "Danny Carey";

		WHEN("creating a person")
		{
			CPerson p(name);

			THEN("name matches")
			{
				REQUIRE(p.GetName() == name);
			}
		}
	}
}

SCENARIO("creating a police man")
{
	GIVEN("a name")
	{
		std::string const name = "Mike Portnoy";

		AND_GIVEN("department name")
		{
			std::string const departmentName = "NYPD";

			WHEN("creating a police man")
			{
				CPoliceMan p(name, departmentName);

				THEN("name matches")
				{
					REQUIRE(p.GetName() == name);
				}

				THEN("department name matches")
				{
					REQUIRE(p.GetDepartmentName() == departmentName);
				}
			}
		}
	}
}

SCENARIO("creating a racer")
{
	GIVEN("a name")
	{
		std::string const name = "James Hetfield";

		AND_GIVEN("awards count")
		{
			std::size_t const awardsCount = 42;

			WHEN("creating a racer")
			{
				CRacer p(name, awardsCount);

				THEN("name matches")
				{
					REQUIRE(p.GetName() == name);
				}

				THEN("awards count matches")
				{
					REQUIRE(p.GetAwardsCount() == awardsCount);
				}
			}
		}
	}
}

SCENARIO("working with a bus")
{
	GIVEN("place count")
	{
		std::size_t const placeCount = 2;

		WHEN("creating a bus")
		{
			CBus bus(placeCount);

			THEN("place count matches")
			{
				REQUIRE(bus.GetPlaceCount() == placeCount);
			}

			THEN("it is empty")
			{
				REQUIRE(bus.IsEmpty());
			}

			THEN("it is not full")
			{
				REQUIRE_FALSE(bus.IsFull());
			}

			THEN("it has zero passengers")
			{
				REQUIRE(bus.GetPassengerCount() == 0);
			}
		}
	}

	GIVEN("an empty bus with 2 places")
	{
		CBus bus(2);

		WHEN("trying to get a passenger")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(bus.GetPassenger(0), std::out_of_range);
			}
		}

		AND_GIVEN("a passenger")
		{
			std::string const name1 = "William";
			std::shared_ptr<IPerson> passenger1 = std::make_shared<CPerson>(name1);

			WHEN("adding a passenger")
			{
				bus.AddPassenger(passenger1);

				THEN("bus is not empty")
				{
					REQUIRE_FALSE(bus.IsEmpty());
				}

				THEN("bus is not full")
				{
					REQUIRE_FALSE(bus.IsFull());
				}

				THEN("passenger count equals 1")
				{
					REQUIRE(bus.GetPassengerCount() == 1);
				}

				THEN("first passenger matches")
				{
					auto const& p = bus.GetPassenger(0);
					REQUIRE(p.GetName() == name1);
				}

				AND_GIVEN("another passenger")
				{
					std::string const name2 = "John";
					std::shared_ptr<IPerson> passenger2 = std::make_shared<CPerson>(name2);

					AND_WHEN("adding another passenger")
					{
						bus.AddPassenger(passenger2);

						THEN("bus is not empty")
						{
							REQUIRE_FALSE(bus.IsEmpty());
						}

						THEN("bus is full")
						{
							REQUIRE(bus.IsFull());
						}

						THEN("passenger count equals 2")
						{
							REQUIRE(bus.GetPassengerCount() == 2);
						}

						THEN("second passenger matches")
						{
							auto const& p = bus.GetPassenger(1);
							REQUIRE(p.GetName() == name2);
						}

						AND_WHEN("removing all passengers")
						{
							bus.RemoveAllPassengers();

							THEN("bus becomes empty")
							{
								REQUIRE(bus.IsEmpty());
							}
						}

						AND_GIVEN("final passenger")
						{
							std::shared_ptr<IPerson> passenger3 = std::make_shared<CPerson>("Whatever");

							AND_WHEN("adding final passenger")
							{
								THEN("it throws an exception")
								{
									REQUIRE_THROWS_AS(bus.AddPassenger(passenger3), std::logic_error);
								}
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO("working with a police car")
{
	GIVEN("place count")
	{
		std::size_t const placeCount = 2;

		AND_GIVEN("make of the car")
		{
			auto const makeOfTheCar = MakeOfTheCar::TOYOTA;

			WHEN("creating a police car")
			{
				CPoliceCar policeCar(placeCount, makeOfTheCar);

				THEN("place count matches")
				{
					REQUIRE(policeCar.GetPlaceCount() == placeCount);
				}

				THEN("make of the car matches")
				{
					REQUIRE(policeCar.GetMakeOfTheCar() == makeOfTheCar);
				}

				THEN("it is empty")
				{
					REQUIRE(policeCar.IsEmpty());
				}

				THEN("it is not full")
				{
					REQUIRE_FALSE(policeCar.IsFull());
				}

				THEN("it has zero passengers")
				{
					REQUIRE(policeCar.GetPassengerCount() == 0);
				}
			}
		}
	}

	GIVEN("an empty police car with 2 places")
	{
		CPoliceCar policeCar(2, MakeOfTheCar::TOYOTA);

		WHEN("trying to get a passenger")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(policeCar.GetPassenger(0), std::out_of_range);
			}
		}

		AND_GIVEN("a passenger")
		{
			std::string const name1 = "William";
			std::string const departmentName1 = "NYPD";
			std::shared_ptr<IPoliceMan> passenger1 = std::make_shared<CPoliceMan>(name1, departmentName1);

			WHEN("adding a passenger")
			{
				policeCar.AddPassenger(passenger1);

				THEN("police car is not empty")
				{
					REQUIRE_FALSE(policeCar.IsEmpty());
				}

				THEN("police car is not full")
				{
					REQUIRE_FALSE(policeCar.IsFull());
				}

				THEN("passenger count equals 1")
				{
					REQUIRE(policeCar.GetPassengerCount() == 1);
				}

				THEN("first passenger matches")
				{
					auto const& p = policeCar.GetPassenger(0);
					REQUIRE(p.GetName() == name1);
					REQUIRE(p.GetDepartmentName() == departmentName1);
				}

				AND_GIVEN("another passenger")
				{
					std::string const name2 = "John";
					std::string const departmentName2 = "LAPD";
					std::shared_ptr<IPoliceMan> passenger2 = std::make_shared<CPoliceMan>(name2, departmentName2);

					AND_WHEN("adding another passenger")
					{
						policeCar.AddPassenger(passenger2);

						THEN("police car is not empty")
						{
							REQUIRE_FALSE(policeCar.IsEmpty());
						}

						THEN("police car is full")
						{
							REQUIRE(policeCar.IsFull());
						}

						THEN("passenger count equals 2")
						{
							REQUIRE(policeCar.GetPassengerCount() == 2);
						}

						THEN("second passenger matches")
						{
							auto const& p = policeCar.GetPassenger(1);
							REQUIRE(p.GetName() == name2);
							REQUIRE(p.GetDepartmentName() == departmentName2);
						}

						AND_WHEN("removing all passengers")
						{
							policeCar.RemoveAllPassengers();

							THEN("police car becomes empty")
							{
								REQUIRE(policeCar.IsEmpty());
							}
						}

						AND_GIVEN("final passenger")
						{
							std::shared_ptr<IPoliceMan> passenger3 = std::make_shared<CPoliceMan>("Whatever", "Whatever x2");

							AND_WHEN("adding final passenger")
							{
								THEN("it throws an exception")
								{
									REQUIRE_THROWS_AS(policeCar.AddPassenger(passenger3), std::logic_error);
								}
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO("working with a racing car")
{
	GIVEN("place count")
	{
		std::size_t const placeCount = 2;

		AND_GIVEN("make of the car")
		{
			auto const makeOfTheCar = MakeOfTheCar::FORD;

			WHEN("creating a racing car")
			{
				CRacingCar racingCar(placeCount, makeOfTheCar);

				THEN("place count matches")
				{
					REQUIRE(racingCar.GetPlaceCount() == placeCount);
				}

				THEN("make of the car matches")
				{
					REQUIRE(racingCar.GetMakeOfTheCar() == makeOfTheCar);
				}

				THEN("it is empty")
				{
					REQUIRE(racingCar.IsEmpty());
				}

				THEN("it is not full")
				{
					REQUIRE_FALSE(racingCar.IsFull());
				}

				THEN("it has zero passengers")
				{
					REQUIRE(racingCar.GetPassengerCount() == 0);
				}
			}
		}
	}

	GIVEN("an empty racing car with 2 places")
	{
		CRacingCar racingCar(2, MakeOfTheCar::FORD);

		WHEN("trying to get a passenger")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(racingCar.GetPassenger(0), std::out_of_range);
			}
		}

		AND_GIVEN("a passenger")
		{
			std::string const name1 = "William";
			std::size_t const awardsCount1 = 12;
			std::shared_ptr<IRacer> passenger1 = std::make_shared<CRacer>(name1, awardsCount1);

			WHEN("adding a passenger")
			{
				racingCar.AddPassenger(passenger1);

				THEN("racing car is not empty")
				{
					REQUIRE_FALSE(racingCar.IsEmpty());
				}

				THEN("racing car is not full")
				{
					REQUIRE_FALSE(racingCar.IsFull());
				}

				THEN("passenger count equals 1")
				{
					REQUIRE(racingCar.GetPassengerCount() == 1);
				}

				THEN("first passenger matches")
				{
					auto const& p = racingCar.GetPassenger(0);
					REQUIRE(p.GetName() == name1);
					REQUIRE(p.GetAwardsCount() == awardsCount1);
				}

				AND_GIVEN("another passenger")
				{
					std::string const name2 = "John";
					std::size_t const awardsCount2 = 30;
					std::shared_ptr<IRacer> passenger2 = std::make_shared<CRacer>(name2, awardsCount2);

					AND_WHEN("adding another passenger")
					{
						racingCar.AddPassenger(passenger2);

						THEN("racing car is not empty")
						{
							REQUIRE_FALSE(racingCar.IsEmpty());
						}

						THEN("racing car is full")
						{
							REQUIRE(racingCar.IsFull());
						}

						THEN("passenger count equals 2")
						{
							REQUIRE(racingCar.GetPassengerCount() == 2);
						}

						THEN("second passenger matches")
						{
							auto const& p = racingCar.GetPassenger(1);
							REQUIRE(p.GetName() == name2);
							REQUIRE(p.GetAwardsCount() == awardsCount2);
						}

						AND_WHEN("removing all passengers")
						{
							racingCar.RemoveAllPassengers();

							THEN("racing car becomes empty")
							{
								REQUIRE(racingCar.IsEmpty());
							}
						}

						AND_GIVEN("final passenger")
						{
							std::shared_ptr<IRacer> passenger3 = std::make_shared<CRacer>("Whatever", 0);

							AND_WHEN("adding final passenger")
							{
								THEN("it throws an exception")
								{
									REQUIRE_THROWS_AS(racingCar.AddPassenger(passenger3), std::logic_error);
								}
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO("working with a taxi")
{
	GIVEN("place count")
	{
		std::size_t const placeCount = 2;

		AND_GIVEN("make of the car")
		{
			auto const makeOfTheCar = MakeOfTheCar::NISSAN;

			WHEN("creating a taxi")
			{
				CTaxi taxi(placeCount, makeOfTheCar);

				THEN("place count matches")
				{
					REQUIRE(taxi.GetPlaceCount() == placeCount);
				}

				THEN("make of the car matches")
				{
					REQUIRE(taxi.GetMakeOfTheCar() == makeOfTheCar);
				}

				THEN("it is empty")
				{
					REQUIRE(taxi.IsEmpty());
				}

				THEN("it is not full")
				{
					REQUIRE_FALSE(taxi.IsFull());
				}

				THEN("it has zero passengers")
				{
					REQUIRE(taxi.GetPassengerCount() == 0);
				}
			}
		}
	}

	GIVEN("an empty taxi with 2 places")
	{
		CTaxi taxi(2, MakeOfTheCar::NISSAN);

		WHEN("trying to get a passenger")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(taxi.GetPassenger(0), std::out_of_range);
			}
		}

		AND_GIVEN("a passenger")
		{
			std::string const name1 = "William";
			std::shared_ptr<IPerson> passenger1 = std::make_shared<CPerson>(name1);

			WHEN("adding a passenger")
			{
				taxi.AddPassenger(passenger1);

				THEN("taxi is not empty")
				{
					REQUIRE_FALSE(taxi.IsEmpty());
				}

				THEN("taxi is not full")
				{
					REQUIRE_FALSE(taxi.IsFull());
				}

				THEN("passenger count equals 1")
				{
					REQUIRE(taxi.GetPassengerCount() == 1);
				}

				THEN("first passenger matches")
				{
					auto const& p = taxi.GetPassenger(0);
					REQUIRE(p.GetName() == name1);
				}

				AND_GIVEN("another passenger")
				{
					std::string const name2 = "John";
					std::shared_ptr<IPerson> passenger2 = std::make_shared<CPerson>(name2);

					AND_WHEN("adding another passenger")
					{
						taxi.AddPassenger(passenger2);

						THEN("taxi is not empty")
						{
							REQUIRE_FALSE(taxi.IsEmpty());
						}

						THEN("taxi is full")
						{
							REQUIRE(taxi.IsFull());
						}

						THEN("passenger count equals 2")
						{
							REQUIRE(taxi.GetPassengerCount() == 2);
						}

						THEN("second passenger matches")
						{
							auto const& p = taxi.GetPassenger(1);
							REQUIRE(p.GetName() == name2);
						}

						AND_WHEN("removing all passengers")
						{
							taxi.RemoveAllPassengers();

							THEN("taxi becomes empty")
							{
								REQUIRE(taxi.IsEmpty());
							}
						}

						AND_GIVEN("final passenger")
						{
							std::shared_ptr<IPerson> passenger3 = std::make_shared<CPerson>("Whatever");

							AND_WHEN("adding final passenger")
							{
								THEN("it throws an exception")
								{
									REQUIRE_THROWS_AS(taxi.AddPassenger(passenger3), std::logic_error);
								}
							}
						}
					}
				}
			}
		}
	}
}
