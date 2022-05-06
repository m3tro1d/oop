#define CATCH_CONFIG_MAIN
#include "../CStringStack.h"
#include "../CStringStackUnderflowError.h"
#include "catch.hpp"

SCENARIO("creating a stack")
{
	GIVEN("nothing")
	{
		WHEN("stack is created")
		{
			CStringStack stack;

			THEN("it's empty")
			{
				REQUIRE(stack.IsEmpty());
			}

			THEN("size equals 0")
			{
				REQUIRE(stack.GetSize() == 0);
			}
		}
	}

	GIVEN("another empty stack")
	{
		CStringStack original;

		WHEN("copying")
		{
			// TODO
		}

		WHEN("moving to another stack")
		{
			CStringStack stack = std::move(original);

			THEN("it is empty")
			{
				REQUIRE(stack.IsEmpty());
			}

			THEN("size equals 0")
			{
				REQUIRE(stack.GetSize() == 0);
			}

			THEN("original is still empty")
			{
				REQUIRE(original.IsEmpty());
			}

			THEN("original size equals 0")
			{
				REQUIRE(original.GetSize() == 0);
			}
		}
	}

	GIVEN("another stack with one element")
	{
		CStringStack original;
		std::string const element = "hello";
		original.Push(element);

		WHEN("copying")
		{
			// TODO
		}

		WHEN("moving")
		{
			CStringStack stack = std::move(original);

			THEN("it is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 1")
			{
				REQUIRE(stack.GetSize() == 1);
			}

			THEN("top element matches the original one")
			{
				REQUIRE(stack.Top() == element);
			}

			THEN("original becomes empty")
			{
				REQUIRE(original.IsEmpty());
			}

			THEN("original size equals 0")
			{
				REQUIRE(original.GetSize() == 0);
			}
		}
	}

	GIVEN("another stack with several elements")
	{
		CStringStack original;
		std::string const element1 = "hello";
		std::string const element2 = "world";
		std::string const element3 = "and bye";
		original.Push(element1);
		original.Push(element2);
		original.Push(element3);

		WHEN("copying")
		{
			// TODO
		}

		WHEN("moving")
		{
			CStringStack stack = std::move(original);

			THEN("it is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 1")
			{
				REQUIRE(stack.GetSize() == 3);
			}

			THEN("elements match the original ones")
			{
				REQUIRE(stack.Top() == element3);
				stack.Pop();
				REQUIRE(stack.Top() == element2);
				stack.Pop();
				REQUIRE(stack.Top() == element1);
			}

			THEN("original becomes empty")
			{
				REQUIRE(original.IsEmpty());
			}

			THEN("original size equals 0")
			{
				REQUIRE(original.GetSize() == 0);
			}
		}
	}
}

SCENARIO("assigning a stack")
{
	GIVEN("source stack with several elements")
	{
		CStringStack source;
		std::string const sourceElement1 = "I, rule the midnight air the destroyer";
		std::string const sourceElement2 = "Born, I shall soon be there, deadly mass";
		source.Push(sourceElement1);
		source.Push(sourceElement2);

		GIVEN("empty stack")
		{
			CStringStack stack;

			WHEN("copying")
			{
				// TODO
			}

			WHEN("moving")
			{
				stack = std::move(source);

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				THEN("source stack becomes empty")
				{
					REQUIRE(source.IsEmpty());
				}

				THEN("source size equals 0")
				{
					REQUIRE(source.GetSize() == 0);
				}
			}
		}

		GIVEN("stack with one element")
		{
			CStringStack stack;
			std::string const element = "hello";
			stack.Push(element);

			WHEN("copying")
			{
				// TODO
			}

			WHEN("moving")
			{
				stack = std::move(source);

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				THEN("source stack becomes empty")
				{
					REQUIRE(source.IsEmpty());
				}

				THEN("source size equals 0")
				{
					REQUIRE(source.GetSize() == 0);
				}
			}
		}

		GIVEN("stack with several elements")
		{
			CStringStack stack;
			std::string const element1 = "Abracadabra boom shacka dae";
			std::string const element2 = "I'm Violent J and I'm back like a vertebrae";
			std::string const element3 = "And I come with a hat full of tricks";
			stack.Push(element1);
			stack.Push(element2);
			stack.Push(element3);

			WHEN("copying")
			{
				// TODO
			}

			WHEN("moving")
			{
				stack = std::move(source);

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				THEN("source stack becomes empty")
				{
					REQUIRE(source.IsEmpty());
				}

				THEN("source size equals 0")
				{
					REQUIRE(source.GetSize() == 0);
				}
			}
		}
	}
}

SCENARIO("getting top element from the stack")
{
	GIVEN("empty stack")
	{
		CStringStack stack;

		WHEN("getting the top element")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(stack.Top(), CStringStackUnderflowError);
			}
		}
	}

	GIVEN("stack with one element")
	{
		CStringStack stack;
		std::string const element = "a tout le monde";
		stack.Push(element);

		WHEN("getting the top element")
		{
			THEN("it returns the added string")
			{
				REQUIRE(stack.Top() == element);
			}
		}
	}

	GIVEN("stack with several elements")
	{
		CStringStack stack;
		std::string const lastElement = "that's what she said";
		stack.Push("Somebody once told me the world is gonna roll me");
		stack.Push("I ain't the sharpest tool in the shed");
		stack.Push(lastElement);

		WHEN("getting the top element")
		{
			THEN("it returns the added string")
			{
				REQUIRE(stack.Top() == lastElement);
			}
		}
	}
}

SCENARIO("adding elements to the stack")
{
	GIVEN("empty stack")
	{
		CStringStack stack;

		WHEN("pushing one element")
		{
			std::string const element = "ride";
			stack.Push(element);

			THEN("it's not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 1")
			{
				REQUIRE(stack.GetSize() == 1);
			}

			THEN("top element matches")
			{
				REQUIRE(stack.Top() == element);
			}

			WHEN("pushing more elements")
			{
				std::string const element1 = "the";
				std::string const element2 = "spiral";
				stack.Push(element1);
				stack.Push(element2);

				THEN("it's not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 3")
				{
					REQUIRE(stack.GetSize() == 3);
				}

				THEN("top element matches the last one")
				{
					REQUIRE(stack.Top() == element2);
				}
			}
		}
	}
}

SCENARIO("removing elements from the stack")
{
	GIVEN("empty stack")
	{
		CStringStack stack;

		WHEN("removing an element")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(stack.Pop(), CStringStackUnderflowError);
			}
		}
	}

	GIVEN("stack with one element")
	{
		CStringStack stack;
		stack.Push("You're a fucking penis-hole, grab a dick and eat it whole");

		WHEN("removing an element")
		{
			stack.Pop();

			THEN("it becomes empty")
			{
				REQUIRE(stack.IsEmpty());
			}

			THEN("size equals 0")
			{
				REQUIRE(stack.GetSize() == 0);
			}

			WHEN("removing an element again")
			{
				THEN("it throws an exception")
				{
					REQUIRE_THROWS_AS(stack.Pop(), CStringStackUnderflowError);
				}
			}
		}
	}

	GIVEN("stack with several elements")
	{
		CStringStack stack;
		std::string const aboveLastElement = "You're so fucking ugly and your face is fucking foul, jeez";
		stack.Push("You're a fucking penis-hole, grab a dick and eat it whole");
		stack.Push("I need to know if you were dropped when you were just a fetus though");
		stack.Push(aboveLastElement);
		stack.Push("You're so fucking loud, can you shut your fucking mouth, can you");

		WHEN("removing an element")
		{
			stack.Pop();

			THEN("it doesn't become empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 3")
			{
				REQUIRE(stack.GetSize() == 3);
			}

			THEN("top element is the above last one")
			{
				REQUIRE(stack.Top() == aboveLastElement);
			}
		}
	}
}
