#define CATCH_CONFIG_MAIN
#include "../People/CPerson.h"
#include "../People/CPoliceMan.h"
#include "../People/CRacer.h"
#include "../Vehicles/CBus.h"
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
}

SCENARIO("working with a racing car")
{
}

SCENARIO("working with a taxi")
{
}
