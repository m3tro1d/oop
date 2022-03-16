#define CATCH_CONFIG_MAIN
#include "../Shapes/SolidShapes/Circle/CCircle.h"
#include "../Shapes/SolidShapes/Rectangle/CRectangle.h"
#include "../Shapes/SolidShapes/Triangle/CTriangle.h"
#include "catch.hpp"

bool ApproximatelyEquals(double a, double b)
{
	return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

TEST_CASE("figures work correctly")
{
	SECTION("point operations work correctly")
	{
		SECTION("creating a point saves its coordinates")
		{
			double x = 12;
			double y = 43.5;
			CPoint p(x, y);

			REQUIRE(p.GetX() == x);
			REQUIRE(p.GetY() == y);
		}

		SECTION("distance calculation between two points works correctly")
		{
			CPoint p1(0, 0);
			CPoint p2(3, 4);

			SECTION("distance between different points is more than zero")
			{
				auto distance = CPoint::Distance(p1, p2);
				REQUIRE(ApproximatelyEquals(distance, 5));
			}

			SECTION("distance between same points is zero")
			{
				auto distance = CPoint::Distance(p1, p1);
				REQUIRE(ApproximatelyEquals(distance, 0));
			}

			SECTION("distance calculation is commutative")
			{
				auto distance1 = CPoint::Distance(p1, p2);
				auto distance2 = CPoint::Distance(p2, p1);
				REQUIRE(ApproximatelyEquals(distance1, distance2));
			}
		}
	}

	SECTION("circle operations work correctly")
	{
		// TODO
	}

	SECTION("rectangle operations work correctly")
	{
		// TODO
	}

	SECTION("triangle operations work correctly")
	{
		// TODO
	}
}

// TODO: program control tests
