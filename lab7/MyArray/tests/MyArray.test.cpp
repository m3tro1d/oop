#define CATCH_CONFIG_MAIN
#include "../CMyArray.hpp"
#include "catch.hpp"

SCENARIO("creating an array")
{
	GIVEN("nothing")
	{
		WHEN("creating an array")
		{
			CMyArray<int> array;

			THEN("size equals 0")
			{
				REQUIRE(array.GetSize() == 0);
			}
		}
	}

	GIVEN("initial size")
	{
		size_t const size = 3;

		WHEN("creating an array")
		{
			CMyArray<int> array(size);

			THEN("size matches the given one")
			{
				REQUIRE(array.GetSize() == size);
			}
		}
	}

	GIVEN("other empty array")
	{
		CMyArray<int> original;

		WHEN("copying")
		{
			CMyArray array(original);

			THEN("size equals 0")
			{
				REQUIRE(array.GetSize() == 0);
			}

			THEN("original stays empty")
			{
				REQUIRE(original.GetSize() == 0);
			}

			WHEN("the original one is changed")
			{
				original.Push(12);

				THEN("the copy is not affected")
				{
					REQUIRE(array.GetSize() == 0);
				}
			}
		}

		WHEN("moving")
		{
			CMyArray array(std::move(original));

			THEN("size equals 0")
			{
				REQUIRE(array.GetSize() == 0);
			}

			THEN("original stays empty")
			{
				REQUIRE(original.GetSize() == 0);
			}
		}
	}

	GIVEN("other filled array")
	{
		CMyArray<int> original;
		int const element1 = 12;
		int const element2 = 17;
		int const element3 = 36;
		original.Push(element1);
		original.Push(element2);
		original.Push(element3);
		size_t const originalSize = original.GetSize();

		WHEN("copying")
		{
			CMyArray array(original);

			THEN("size matches the original")
			{
				REQUIRE(array.GetSize() == originalSize);
			}

			THEN("original size still matches")
			{
				REQUIRE(original.GetSize() == originalSize);
			}

			THEN("original elements match")
			{
				REQUIRE(array[0] == element1);
				REQUIRE(array[1] == element2);
				REQUIRE(array[2] == element3);
			}

			WHEN("the original one is changed")
			{
				original.Push(42);

				THEN("the copy is not affected")
				{
					REQUIRE(array.GetSize() == originalSize);
				}
			}
		}

		WHEN("moving")
		{
			CMyArray array(std::move(original));

			THEN("size matches the original")
			{
				REQUIRE(array.GetSize() == originalSize);
			}

			THEN("original becomes empty")
			{
				REQUIRE(original.GetSize() == 0);
			}
		}
	}
}

SCENARIO("assigning to the array")
{
}

SCENARIO("adding elements in the end")
{
}

SCENARIO("getting size of the array")
{
}

SCENARIO("accessing elements by index")
{
}

SCENARIO("resizing the array")
{
}

SCENARIO("clearing the array")
{
}

SCENARIO("working with iterators")
{
}
