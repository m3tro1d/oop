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
	GIVEN("source array with several elements")
	{
		CMyArray<std::string> source;
		std::string const sourceElement1 = "The city's cold blood calls me home";
		std::string const sourceElement2 = "Home, it's what I long for";
		source.Push(sourceElement1);
		source.Push(sourceElement2);
		size_t const sourceSize = source.GetSize();

		AND_GIVEN("empty array")
		{
			CMyArray<std::string> array;

			WHEN("copying")
			{
				array = source;

				THEN("size equals 2")
				{
					REQUIRE(array.GetSize() == sourceSize);
				}

				THEN("source size is unchanged")
				{
					REQUIRE(source.GetSize() == sourceSize);
				}

				THEN("elements match")
				{
					REQUIRE(array[0] == sourceElement1);
					REQUIRE(array[1] == sourceElement2);
				}

				WHEN("modifying the source")
				{
					source.Push("A little stitious");

					THEN("it doesn't affect the copy")
					{
						REQUIRE(array.GetSize() == sourceSize);
					}
				}
			}

			WHEN("moving")
			{
				array = std::move(source);

				THEN("size equals 2")
				{
					REQUIRE(array.GetSize() == sourceSize);
				}

				THEN("source becomes empty")
				{
					REQUIRE(source.GetSize() == 0);
				}

				THEN("elements match")
				{
					REQUIRE(array[0] == sourceElement1);
					REQUIRE(array[1] == sourceElement2);
				}
			}
		}

		AND_GIVEN("array with several elements")
		{
			CMyArray<std::string> array;
			std::string const element1 = "Warrior\n"
										 "Strugglin'\n"
										 "To remain\n"
										 "Relevant";
			std::string const element2 = "Warrior\n"
										 "Strugglin'\n"
										 "To remain\n"
										 "Consequential";

			WHEN("copying")
			{
				array = source;

				THEN("size equals 2")
				{
					REQUIRE(array.GetSize() == sourceSize);
				}

				THEN("source size is unchanged")
				{
					REQUIRE(source.GetSize() == sourceSize);
				}

				THEN("elements match")
				{
					REQUIRE(array[0] == sourceElement1);
					REQUIRE(array[1] == sourceElement2);
				}

				WHEN("modifying the source")
				{
					source.Push("A little stitious");

					THEN("it doesn't affect the copy")
					{
						REQUIRE(array.GetSize() == sourceSize);
					}
				}
			}

			WHEN("moving")
			{
				array = std::move(source);

				THEN("size equals 2")
				{
					REQUIRE(array.GetSize() == sourceSize);
				}

				THEN("source becomes empty")
				{
					REQUIRE(source.GetSize() == 0);
				}

				THEN("elements match")
				{
					REQUIRE(array[0] == sourceElement1);
					REQUIRE(array[1] == sourceElement2);
				}
			}
		}

		WHEN("copy-assigning array to itself")
		{
			source = source;

			THEN("it doesn't change")
			{
				REQUIRE(source.GetSize() == sourceSize);

				REQUIRE(source[0] == sourceElement1);
				REQUIRE(source[1] == sourceElement2);
			}
		}

		WHEN("move-assigning array to itself")
		{
			source = std::move(source);

			THEN("it doesn't change")
			{
				REQUIRE(source.GetSize() == sourceSize);

				REQUIRE(source[0] == sourceElement1);
				REQUIRE(source[1] == sourceElement2);
			}
		}
	}
}

SCENARIO("adding elements in the end")
{
	GIVEN("empty array")
	{
		CMyArray<double> array;

		AND_GIVEN("an element")
		{
			double const element1 = 12.43;

			WHEN("adding the element")
			{
				array.Push(element1);

				THEN("size equals 1")
				{
					REQUIRE(array.GetSize() == 1);
				}

				THEN("element matches")
				{
					REQUIRE(array[0] == element1);
				}

				AND_GIVEN("another element")
				{
					double const element2 = 56.33;

					WHEN("adding another element")
					{
						array.Push(element2);

						THEN("size equals 2")
						{
							REQUIRE(array.GetSize() == 2);
						}

						THEN("the last element matches")
						{
							REQUIRE(array[1] == element2);
						}

						THEN("first element is left intact")
						{
							REQUIRE(array[0] == element1);
						}
					}
				}
			}
		}
	}
}

SCENARIO("getting size of the array")
{
	GIVEN("an empty array")
	{
		CMyArray<long> array;

		THEN("size equals 0")
		{
			REQUIRE(array.GetSize() == 0);
		}
	}

	GIVEN("array with one element")
	{
		CMyArray<float> array;
		array.Push(12.5);

		THEN("size equals 1")
		{
			REQUIRE(array.GetSize() == 1);
		}
	}

	GIVEN("array with several elements")
	{
		CMyArray<std::vector<int>> array;
		array.Push({ 1, 1 });
		array.Push({ 1, 1, 2 });
		array.Push({ 1, 1, 2, 3 });
		array.Push({ 1, 1, 2, 3, 5 });

		THEN("size equals 4")
		{
			REQUIRE(array.GetSize() == 4);
		}
	}
}

SCENARIO("accessing elements by index")
{
	// TODO
}

SCENARIO("resizing the array")
{
	// TODO
}

SCENARIO("clearing the array")
{
	GIVEN("an empty array")
	{
		CMyArray<int> array;

		WHEN("clearing the array")
		{
			array.Clear();

			THEN("it remains empty")
			{
				REQUIRE(array.GetSize() == 0);
			}
		}
	}

	GIVEN("array with several elements")
	{
		CMyArray<std::string> array;
		array.Push("Tears in my eyes, chasing Ponce de Leon's phantom soul");
		array.Push("Filled with hope, I can taste mythical fountains");
		array.Push("False hope, perhaps");

		WHEN("clearing the array")
		{
			array.Clear();

			THEN("it becomes empty")
			{
				REQUIRE(array.GetSize() == 0);
			}
		}
	}
}

SCENARIO("working with iterators")
{
	// TODO
}
