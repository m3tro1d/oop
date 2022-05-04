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

		WHEN("stack is created")
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

			WHEN("it is modified")
			{
				stack.Push("hello");

				THEN("original stack stays the same")
				{
					REQUIRE(original.IsEmpty());
					REQUIRE(original.GetSize() == 0);
				}
			}
		}
	}

	GIVEN("another stack with one element")
	{
		CStringStack original;
		std::string const element = "hello";
		original.Push(element);

		WHEN("stack is created")
		{
			CStringStack stack = original;

			THEN("it is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("it has the same size")
			{
				REQUIRE(stack.GetSize() == original.GetSize());
			}

			THEN("it has the same element")
			{
				REQUIRE(original.Top() == stack.Top());
			}

			WHEN("it is modified")
			{
				stack.Push("another");

				THEN("original stack stays the same")
				{
					REQUIRE_FALSE(original.IsEmpty());
					REQUIRE(original.GetSize() == 1);
				}
			}
		}
	}

	GIVEN("another stack with several elements")
	{
		// TODO
	}
}
