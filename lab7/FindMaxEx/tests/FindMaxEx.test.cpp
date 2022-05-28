#define CATCH_CONFIG_MAIN
#include "../FindMaxEx.hpp"
#include "catch.hpp"

SCENARIO("find max element in an empty vector")
{
	GIVEN("an empty vector")
	{
		std::vector<int> vector;

		AND_GIVEN("output variable with a value")
		{
			int result = 1337;

			WHEN("finding max")
			{
				auto found = FindMaxEx(vector, result, [](int l, int r) {
					return l < r;
				});

				THEN("it is not found")
				{
					REQUIRE_FALSE(found);
				}

				THEN("output variable is unchanged")
				{
					REQUIRE(result == 1337);
				}
			}
		}
	}
}

SCENARIO("find max element in the vector containing one element")
{
	GIVEN("a vector with one element")
	{
		int const element = 12;
		std::vector<int> vector{ element };

		AND_GIVEN("output variable with a value")
		{
			int result = 1337;

			WHEN("finding max")
			{
				auto found = FindMaxEx(vector, result, [](int l, int r) {
					return l < r;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("it equals to that single element")
				{
					REQUIRE(result == element);
				}
			}
		}
	}
}

SCENARIO("find max element in not empty vector with different value types")
{
	GIVEN("a vector of integers")
	{
		std::vector<int> vector{ 1, -3, 12, 9, 5, 12 };

		AND_GIVEN("output variable with a value")
		{
			int result = 1337;

			WHEN("finding max")
			{
				auto found = FindMaxEx(vector, result, [](int l, int r) {
					return l < r;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("the value is correct")
				{
					REQUIRE(result == 12);
				}
			}
		}
	}

	GIVEN("a vector of doubles")
	{
		std::vector<double> vector{ 2.9, 12.67, -3.9, 2, 34.5, 9.3 };

		AND_GIVEN("output variable with a value")
		{
			double result = 1337.422;

			WHEN("finding max")
			{
				auto found = FindMaxEx(vector, result, [](double l, double r) {
					return std::abs(l - r) >= std::numeric_limits<double>::epsilon() && l < r;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("the value is correct")
				{
					REQUIRE(result == 34.5);
				}
			}
		}
	}

	GIVEN("a vector of C-strings")
	{
		std::vector<char const*> vector{
			"Now look at them yo-yos, that's the way you do it",
			"You play the guitar on the MTV",
			"That ain't workin', that's the way you do it",
			"Money for nothin' and your chicks for free",
		};

		AND_GIVEN("output variable with a value")
		{
			char const* result = "whatever";

			WHEN("finding max")
			{
				auto found = FindMaxEx(vector, result, [](char const* l, char const* r) {
					return std::strcmp(l, r) < 0;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("the value is correct")
				{
					REQUIRE(std::strcmp(result, "You play the guitar on the MTV") == 0);
				}
			}
		}
	}

	GIVEN("a vector of structs")
	{
		struct Person
		{
			std::string name;
			int age;
		};

		std::vector<Person> vector = {
			{ "Danny Carey", 37 },
			{ "Mike Portnoy", 40 },
			{ "Dimebag Darrel", 19 },
		};

		AND_GIVEN("output variable with a value")
		{
			Person result{ "Violent J", 18 };

			WHEN("finding max by string")
			{
				auto found = FindMaxEx(vector, result, [](Person const& l, Person const& r) {
					return l.name > r.name;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("the value is correct")
				{
					REQUIRE(result.name == "Danny Carey");
					REQUIRE(result.age == 37);
				}
			}

			WHEN("finding max by integer")
			{
				auto found = FindMaxEx(vector, result, [](Person const& l, Person const& r) {
					return l.age < r.age;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("the value is correct")
				{
					REQUIRE(result.name == "Mike Portnoy");
					REQUIRE(result.age == 40);
				}
			}
		}
	}
}

SCENARIO("error during finding max element")
{
	GIVEN("type with faulty copy assignment operator")
	{
		class Test
		{
		public:
			Test(int value)
				: m_value(value)
			{
			}

			Test& operator=(Test const& other)
			{
				throw std::runtime_error("oops");
			}

			int GetValue() const
			{
				return m_value;
			}

		private:
			int m_value;
		};

		AND_GIVEN("vector with values")
		{
			std::vector<Test> vector{ Test(12), Test(-1), Test(5) };

			AND_GIVEN("output variable")
			{
				int const initialValue = 42;
				Test result = initialValue;

				WHEN("trying to find max and catching exception")
				{
					try
					{
						FindMaxEx(vector, result, [](Test const& l, Test const& r) {
							return l.GetValue() < r.GetValue();
						});
					}
					catch (...)
					{
					}

					THEN("output variable isn't changed")
					{
						REQUIRE(result.GetValue() == initialValue);
					}
				}
			}
		}
	}
}
