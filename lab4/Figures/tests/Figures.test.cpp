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
		CPoint center(12, 3);
		double radius = 4;
		uint32_t outlineColor = 0xFF0000;
		uint32_t fillColor = 0xFF0055;
		CCircle circle(center, radius, outlineColor, fillColor);

		SECTION("creating a circle saves its center and radius")
		{
			REQUIRE(ApproximatelyEquals(circle.GetCenter().GetX(), center.GetX()));
			REQUIRE(ApproximatelyEquals(circle.GetCenter().GetY(), center.GetY()));
			REQUIRE(circle.GetRadius() == radius);
		}

		SECTION("circle area is calculated correctly")
		{
			double expected = M_PI * radius * radius;
			REQUIRE(ApproximatelyEquals(circle.GetArea(), expected));
		}

		SECTION("circle perimeter is calculated correctly")
		{
			double expected = 2 * M_PI * radius;
			REQUIRE(ApproximatelyEquals(circle.GetPerimeter(), expected));
		}
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
