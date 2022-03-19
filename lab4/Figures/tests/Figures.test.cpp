#define CATCH_CONFIG_MAIN
#include "../Shapes/SolidShapes/Circle/CCircle.h"
#include "../Shapes/SolidShapes/Rectangle/CRectangle.h"
#include "../Shapes/SolidShapes/Triangle/CTriangle.h"
#include "catch.hpp"

bool ApproximatelyEquals(double a, double b)
{
	return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

TEST_CASE("shapes work correctly")
{
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0xFF0055;

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

	SECTION("line segment operations work correctly")
	{

	}

	SECTION("circle operations work correctly")
	{
		CPoint center(12, 3);
		double radius = 4;
		CCircle circle(center, radius, outlineColor, fillColor);

		SECTION("creating a circle saves its center, radius and colors")
		{
			REQUIRE(circle.GetCenter().GetX() == center.GetX());
			REQUIRE(circle.GetCenter().GetY() == center.GetY());
			REQUIRE(circle.GetRadius() == radius);

			REQUIRE(circle.GetOutlineColor() == outlineColor);
			REQUIRE(circle.GetFillColor() == fillColor);
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
		CPoint leftTop(3, 12);
		CPoint rightBottom(10, 5);
		CRectangle rectangle(leftTop, rightBottom, outlineColor, fillColor);

		SECTION("creating a rectangle saves its points")
		{
			REQUIRE(rectangle.GetLeftTop().GetX() == leftTop.GetX());
			REQUIRE(rectangle.GetLeftTop().GetY() == leftTop.GetY());
			REQUIRE(rectangle.GetRightBottom().GetX() == rightBottom.GetX());
			REQUIRE(rectangle.GetRightBottom().GetY() == rightBottom.GetY());

			REQUIRE(rectangle.GetOutlineColor() == outlineColor);
			REQUIRE(rectangle.GetFillColor() == fillColor);
		}

		SECTION("width and height are calculated correctly")
		{
			double expectedWidth = rightBottom.GetX() - leftTop.GetX();
			REQUIRE(ApproximatelyEquals(rectangle.GetWidth(), expectedWidth));

			double expectedHeight = leftTop.GetY() - rightBottom.GetY();
			REQUIRE(ApproximatelyEquals(rectangle.GetHeight(), expectedHeight));
		}

		SECTION("rectangle area is calculated correctly")
		{
			double expected = (rightBottom.GetX() - leftTop.GetX()) * (leftTop.GetY() - rightBottom.GetY());
			REQUIRE(ApproximatelyEquals(rectangle.GetArea(), expected));
		}

		SECTION("rectangle perimeter is calculated correctly")
		{
			double expected = 2 * ((rightBottom.GetX() - leftTop.GetX()) + (leftTop.GetY() - rightBottom.GetY()));
			REQUIRE(ApproximatelyEquals(rectangle.GetPerimeter(), expected));
		}
	}

	SECTION("triangle operations work correctly")
	{
		CPoint vertex1(0, 0);
		CPoint vertex2(2, 0);
		CPoint vertex3(2, 3);
		CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

		SECTION("creating a triangle saves its vertices")
		{
			REQUIRE(triangle.GetVertex1().GetX() == vertex1.GetX());
			REQUIRE(triangle.GetVertex1().GetY() == vertex1.GetY());
			REQUIRE(triangle.GetVertex2().GetX() == vertex2.GetX());
			REQUIRE(triangle.GetVertex2().GetY() == vertex2.GetY());
			REQUIRE(triangle.GetVertex3().GetX() == vertex3.GetX());
			REQUIRE(triangle.GetVertex3().GetY() == vertex3.GetY());

			REQUIRE(triangle.GetOutlineColor() == outlineColor);
			REQUIRE(triangle.GetFillColor() == fillColor);
		}

		SECTION("triangle area is calculated correctly")
		{
			double expected = CPoint::Distance(vertex1, vertex2) * CPoint::Distance(vertex2, vertex3) / 2;
			REQUIRE(ApproximatelyEquals(triangle.GetArea(), expected));
		}

		SECTION("triangle perimeter is calculated correctly")
		{
			double expected = CPoint::Distance(vertex1, vertex2) + CPoint::Distance(vertex2, vertex3) + CPoint::Distance(vertex3, vertex1);
			REQUIRE(ApproximatelyEquals(triangle.GetPerimeter(), expected));
		}
	}
}

// TODO: program control tests
