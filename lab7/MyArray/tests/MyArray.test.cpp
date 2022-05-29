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

	GIVEN("type with faulty copy constructor")
	{
		class Test
		{
		public:
			Test() = default;

			Test(Test const& other)
			{
				throw std::runtime_error("oops");
			}

			int GetValue() const
			{
				return m_value;
			}

		private:
			int m_value = 12;
		};

		AND_GIVEN("array of values")
		{
			CMyArray<Test> original;
			original.Push(Test());

			WHEN("copying and catching an exception")
			{
				try
				{
					CMyArray array(original);
				}
				catch (...)
				{
				}

				THEN("original size stays the same")
				{
					REQUIRE(original.GetSize() == 1);
				}

				THEN("original element matches")
				{
					REQUIRE(original[0].GetValue() == 12);
				}
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
	GIVEN("an empty array")
	{
		CMyArray<int> array;

		WHEN("accessing any element")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(array[-1], std::out_of_range);
				REQUIRE_THROWS_AS(array[0], std::out_of_range);
				REQUIRE_THROWS_AS(array[1], std::out_of_range);
			}
		}

		WHEN("assigning to any element")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(array[-1] = 1, std::out_of_range);
				REQUIRE_THROWS_AS(array[0] = 1, std::out_of_range);
				REQUIRE_THROWS_AS(array[1] = 1, std::out_of_range);
			}
		}
	}

	GIVEN("pre-allocated array")
	{
		CMyArray<std::string> array(1);

		WHEN("accessing the first element")
		{
			auto element = array[0];

			THEN("it has default value")
			{
				REQUIRE(element.empty());
			}
		}

		WHEN("accessing other elements")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(array[-1], std::out_of_range);
				REQUIRE_THROWS_AS(array[1], std::out_of_range);
			}
		}

		WHEN("assigning to the first element")
		{
			std::string value = "Blame it all on the bastards when you're blowing out";
			array[0] = value;

			THEN("it changes")
			{
				REQUIRE(array[0] == value);
			}
		}

		WHEN("assigning to the elements out of range")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(array[-1] = "", std::out_of_range);
				REQUIRE_THROWS_AS(array[1] = "", std::out_of_range);
			}
		}
	}

	GIVEN("array with several elements")
	{
		CMyArray<std::string> array;
		std::string sourceElement1 = "Heat lighting flash, but don't blink";
		std::string sourceElement2 = "Misleading";
		std::string sourceElement3 = "Tranquility ruse";
		array.Push(sourceElement1);
		array.Push(sourceElement2);
		array.Push(sourceElement3);

		WHEN("accessing the elements within range")
		{
			auto element1 = array[0];
			auto element2 = array[1];
			auto element3 = array[2];

			THEN("elements match")
			{
				REQUIRE(element1 == sourceElement1);
				REQUIRE(element2 == sourceElement2);
				REQUIRE(element3 == sourceElement3);
			}
		}

		WHEN("accessing the elements out of range")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(array[-1], std::out_of_range);
				REQUIRE_THROWS_AS(array[3], std::out_of_range);
			}
		}

		WHEN("assigning to the arbitrary elements")
		{
			std::string const value1 = "A tempest must be";
			std::string const value2 = "True to its nature";
			array[0] = value1;
			array[2] = value2;

			THEN("they change")
			{
				REQUIRE(array[0] == value1);
				REQUIRE(array[2] == value2);
			}

			THEN("unassigned element remains the same")
			{
				REQUIRE(array[1] == sourceElement2);
			}
		}

		WHEN("assigning to the elements out of range")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(array[-1] = "", std::out_of_range);
				REQUIRE_THROWS_AS(array[3] = "", std::out_of_range);
			}
		}
	}
}

SCENARIO("resizing the array")
{
	GIVEN("an empty array")
	{
		CMyArray<std::string> array;

		AND_GIVEN("new size which is the same")
		{
			size_t const newSize = array.GetSize();

			WHEN("resizing the array")
			{
				array.Resize(newSize);

				THEN("it stays empty")
				{
					REQUIRE(array.GetSize() == 0);
				}
			}
		}

		AND_GIVEN("new size which is greater")
		{
			size_t const newSize = array.GetSize() + 2;

			WHEN("resizing the array")
			{
				array.Resize(newSize);

				THEN("size matches")
				{
					REQUIRE(array.GetSize() == newSize);
				}

				THEN("elements have default values")
				{
					REQUIRE(array[0].empty());
					REQUIRE(array[1].empty());
				}
			}
		}
	}

	GIVEN("array with several elements")
	{
		CMyArray<std::string> array;
		std::string const element1 = "Control, your delusion";
		std::string const element2 = "Insane and striking at random";
		std::string const element3 = "Victim of your certainty";
		array.Push(element1);
		array.Push(element2);
		array.Push(element3);

		AND_GIVEN("new zero size")
		{
			size_t const newSize = 0;

			WHEN("resizing the array")
			{
				array.Resize(newSize);

				THEN("it becomes empty")
				{
					REQUIRE(array.GetSize() == newSize);
				}
			}
		}

		AND_GIVEN("new size which is the same")
		{
			size_t const newSize = array.GetSize();

			WHEN("resizing the array")
			{
				array.Resize(newSize);

				THEN("size doesn't change")
				{
					REQUIRE(array.GetSize() == newSize);
				}

				THEN("elements stay the same")
				{
					REQUIRE(array[0] == element1);
					REQUIRE(array[1] == element2);
					REQUIRE(array[2] == element3);
				}
			}
		}

		AND_GIVEN("new size which is less")
		{
			size_t const newSize = array.GetSize() - 1;

			WHEN("resizing the array")
			{
				array.Resize(newSize);

				THEN("size becomes less")
				{
					REQUIRE(array.GetSize() == newSize);
				}

				THEN("elements are truncated")
				{
					REQUIRE(array[0] == element1);
					REQUIRE(array[1] == element2);
					REQUIRE_THROWS_AS(array[2], std::out_of_range);
				}
			}
		}

		AND_GIVEN("new size which is greater")
		{
			size_t const newSize = array.GetSize() + 1;

			WHEN("resizing the array")
			{
				array.Resize(newSize);

				THEN("size becomes greater")
				{
					REQUIRE(array.GetSize() == newSize);
				}

				THEN("initial elements stay the same")
				{
					REQUIRE(array[0] == element1);
					REQUIRE(array[1] == element2);
					REQUIRE(array[2] == element3);
				}

				THEN("new element has the default value")
				{
					REQUIRE(array[3].empty());
				}
			}
		}
	}
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

			AND_WHEN("inserting new elements")
			{
				array.Push("Beating tired bones");
				array.Push("Tripping through remember when");

				THEN("size equals 2")
				{
					REQUIRE(array.GetSize() == 2);
				}

				THEN("new elements match")
				{
					REQUIRE(array[0] == "Beating tired bones");
					REQUIRE(array[1] == "Tripping through remember when");
				}
			}
		}
	}
}

SCENARIO("working with iterators")
{
	GIVEN("an array with several elements")
	{
		CMyArray<std::string> array;

		std::string const element1 = "What the hell's going on?!";
		std::string const element2 = "Can someone tell me please?";
		std::string const element3 = "Why I'm switching faster than the channels on TV?";

		array.Push(element1);
		array.Push(element2);
		array.Push(element3);

		std::string const compilation = "What the hell's going on?!\n"
										"Can someone tell me please?\n"
										"Why I'm switching faster than the channels on TV?\n";
		std::string const compilationReversed = "Why I'm switching faster than the channels on TV?\n"
												"Can someone tell me please?\n"
												"What the hell's going on?!\n";

		std::stringstream output;

		WHEN("iterating from beginning to end")
		{
			for (auto it = array.begin(); it != array.end(); ++it)
			{
				output << *it << '\n';
			}

			THEN("the result matches")
			{
				REQUIRE(output.str() == compilation);
			}
		}

		WHEN("modifying the element through the iterator")
		{
			auto it = array.begin();
			std::string const newElement = "vanilla smile and gorgeous strawberry kiss";
			*it = newElement;

			THEN("the element changes")
			{
				REQUIRE(array[0] == newElement);
			}
		}

		WHEN("using range-based for loop")
		{
			for (auto const& element : array)
			{
				output << element << '\n';
			}

			THEN("the result matches")
			{
				REQUIRE(output.str() == compilation);
			}
		}

		WHEN("iterating from beginning to end in reverse")
		{
			for (auto it = array.rbegin(); it != array.rend(); ++it)
			{
				output << *it << '\n';
			}

			THEN("the result matches")
			{
				REQUIRE(output.str() == compilationReversed);
			}
		}

		WHEN("iterating backwards")
		{
			for (auto it = array.end() - 1; it != array.begin() - 1; --it)
			{
				output << *it << '\n';
			}

			THEN("the result matches")
			{
				REQUIRE(output.str() == compilationReversed);
			}
		}

		WHEN("using std::copy")
		{
			std::copy(
				array.begin(),
				array.end(),
				std::ostream_iterator<std::string>(output, "\n"));

			THEN("it is compatible")
			{
				REQUIRE(output.str() == compilation);
			}
		}

		AND_GIVEN("constant copy of the array")
		{
			CMyArray const arrayConst = array;

			WHEN("iterating from beginning to end")
			{
				for (auto it = arrayConst.cbegin(); it != arrayConst.cend(); ++it)
				{
					output << *it << '\n';
				}

				THEN("the result matches")
				{
					REQUIRE(output.str() == compilation);
				}
			}

			WHEN("using range-based for loop")
			{
				for (auto const& element : arrayConst)
				{
					output << element << '\n';
				}

				THEN("the result matches")
				{
					REQUIRE(output.str() == compilation);
				}
			}

			WHEN("iterating from beginning to end in reverse")
			{
				for (auto it = arrayConst.crbegin(); it != arrayConst.crend(); ++it)
				{
					output << *it << '\n';
				}

				THEN("the result matches")
				{
					REQUIRE(output.str() == compilationReversed);
				}
			}

			WHEN("iterating backwards")
			{
				for (auto it = arrayConst.cend() - 1; it != arrayConst.cbegin() - 1; --it)
				{
					output << *it << '\n';
				}

				THEN("the result matches")
				{
					REQUIRE(output.str() == compilationReversed);
				}
			}

			WHEN("using std::copy")
			{
				std::copy(
					arrayConst.begin(),
					arrayConst.end(),
					std::ostream_iterator<std::string>(output, "\n"));

				THEN("it is compatible")
				{
					REQUIRE(output.str() == compilation);
				}
			}
		}
	}
}

SCENARIO("assigning arrays with different types")
{
	GIVEN("source array of doubles")
	{
		CMyArray<double> source;
		double const element1 = 12.3;
		double const element2 = 42.333;
		double const element3 = 4;

		source.Push(element1);
		source.Push(element2);
		source.Push(element3);

		AND_GIVEN("an array of integers")
		{
			CMyArray<int> array;

			WHEN("assigning array of doubles to an array of integers")
			{
				array = source;

				THEN("size matches")
				{
					REQUIRE(array.GetSize() == source.GetSize());
				}

				THEN("elements match after a cast")
				{
					REQUIRE(array[0] == static_cast<int>(element1));
					REQUIRE(array[1] == static_cast<int>(element2));
					REQUIRE(array[2] == static_cast<int>(element3));
				}
			}
		}
	}

	GIVEN("type with faulty cast to integer operator")
	{
		class Test
		{
		public:
			Test() = default;

			operator int() const
			{
				throw std::runtime_error("oops");
			}

		private:
			int m_value = 0;
		};

		AND_GIVEN("source array of values")
		{
			CMyArray<Test> source;
			source.Push(Test());

			AND_GIVEN("array with integers")
			{
				CMyArray<int> array;
				int const element1 = 3;
				int const element2 = -1;
				int const element3 = 100;

				array.Push(element1);
				array.Push(element2);
				array.Push(element3);

				auto const initialSize = array.GetSize();

				WHEN("assigning array of values to an array of integers and catching exception")
				{
					try
					{
						array = source;
					}
					catch (...)
					{
					}

					THEN("size doesn't change")
					{
						REQUIRE(array.GetSize() == initialSize);
					}

					THEN("elements don't change")
					{
						REQUIRE(array[0] == element1);
						REQUIRE(array[1] == element2);
						REQUIRE(array[2] == element3);
					}
				}
			}
		}
	}
}
