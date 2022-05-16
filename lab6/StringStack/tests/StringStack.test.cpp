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
			CStringStack stack = original;

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

			WHEN("modifying the original doesn't affect the copy")
			{
				original.Push("SPANISH INQUISITION");

				THEN("it doesn't affect the copy")
				{
					REQUIRE(stack.IsEmpty());
				}
			}
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
		std::string const element = "The first little piggy, his house is made of wood\n"
									"He lives in a chicken-turkey-piggy neighborhood";
		original.Push(element);

		WHEN("copying")
		{
			CStringStack stack = original;

			THEN("it is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 1")
			{
				REQUIRE(stack.GetSize() == 1);
			}

			THEN("original is still not empty")
			{
				REQUIRE_FALSE(original.IsEmpty());
			}

			THEN("original size equals 1")
			{
				REQUIRE(original.GetSize() == 1);
			}

			THEN("the element matches")
			{
				REQUIRE(stack.Top() == element);
			}

			WHEN("modifying the original")
			{
				original.Pop();

				THEN("it doesn't affect the copy")
				{
					REQUIRE(stack.Top() == element);
				}
			}
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
		std::string const element1 = "He likes to fuck his sister and drink his moonshine";
		std::string const element2 = "A typical redneck filthy fuckin' swine";
		std::string const element3 = "I rode into town with my axe in my holster";
		original.Push(element1);
		original.Push(element2);
		original.Push(element3);

		WHEN("copying")
		{
			CStringStack stack = original;

			THEN("it is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 3")
			{
				REQUIRE(stack.GetSize() == 3);
			}

			THEN("original is still not empty")
			{
				REQUIRE_FALSE(original.IsEmpty());
			}

			THEN("original size equals 3")
			{
				REQUIRE(original.GetSize() == 3);
			}

			THEN("the elements match")
			{
				REQUIRE(stack.Top() == element3);
				stack.Pop();
				REQUIRE(stack.Top() == element2);
				stack.Pop();
				REQUIRE(stack.Top() == element1);
			}

			WHEN("modifying the original")
			{
				original.Pop();

				THEN("it doesn't affect the copy")
				{
					REQUIRE(stack.Top() == element3);
				}
			}
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
				stack = source;

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source is still not empty")
				{
					REQUIRE_FALSE(source.IsEmpty());
				}

				THEN("source size equals 2")
				{
					REQUIRE(source.GetSize() == 2);
				}

				THEN("the elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				WHEN("modifying the source")
				{
					source.Pop();

					THEN("it doesn't affect the copy")
					{
						REQUIRE(stack.Top() == sourceElement2);
					}
				}
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
			std::string const element = "Three little piggies to make a piggy pie";
			stack.Push(element);

			WHEN("copying")
			{
				stack = source;

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source is still not empty")
				{
					REQUIRE_FALSE(source.IsEmpty());
				}

				THEN("source size equals 2")
				{
					REQUIRE(source.GetSize() == 2);
				}

				THEN("the elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				WHEN("modifying the source")
				{
					source.Pop();

					THEN("it doesn't affect the copy")
					{
						REQUIRE(stack.Top() == sourceElement2);
					}
				}
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
				stack = source;

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source is still not empty")
				{
					REQUIRE_FALSE(source.IsEmpty());
				}

				THEN("source size equals 2")
				{
					REQUIRE(source.GetSize() == 2);
				}

				THEN("the elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				WHEN("modifying the source")
				{
					source.Pop();

					THEN("it doesn't affect the copy")
					{
						REQUIRE(stack.Top() == sourceElement2);
					}
				}
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

		WHEN("copy-assigning stack to itself")
		{
			source = source;

			THEN("it doesn't change")
			{
				REQUIRE_FALSE(source.IsEmpty());
				REQUIRE(source.GetSize() == 2);

				REQUIRE(source.Top() == sourceElement2);
				source.Pop();
				REQUIRE(source.Top() == sourceElement1);
			}
		}

		WHEN("move-assigning stack to itself")
		{
			source = std::move(source);

			THEN("it doesn't change")
			{
				REQUIRE_FALSE(source.IsEmpty());
				REQUIRE(source.GetSize() == 2);

				REQUIRE(source.Top() == sourceElement2);
				source.Pop();
				REQUIRE(source.Top() == sourceElement1);
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
		std::string const element = "The carnival's in town, come and get your piggy snacks";
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
		std::string const lastElement = "The second little piggy, his house is made of brick";
		stack.Push("And this little piggy is a motherfuckin' dick");
		stack.Push("He sits on his bench and gets all the respect");
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
				std::string const element1 = "I can smoke this room before his hearing aid will pick it up";
				std::string const element2 = "Old-ass man, I let him get away";
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
		stack.Push("You're a fucking penis-hole, grab a dick and eat it whole");
		stack.Push("I need to know if you were dropped when you were just a fetus though");
		std::string const aboveLastElement = "You're so fucking ugly and your face is fucking foul, jeez";
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
