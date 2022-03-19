#define CATCH_CONFIG_MAIN
#include "../ShapeProcessor.h"
#include "../Shapes/LineSegment/CLineSegment.h"
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
		CPoint start(12, 3);
		CPoint end(-5, 10);
		CLineSegment line(start, end, outlineColor);

		SECTION("creating a line segment saves its properties")
		{
			REQUIRE(line.GetStartPoint().GetX() == start.GetX());
			REQUIRE(line.GetStartPoint().GetY() == start.GetY());
			REQUIRE(line.GetEndPoint().GetX() == end.GetX());
			REQUIRE(line.GetEndPoint().GetY() == end.GetY());

			REQUIRE(line.GetOutlineColor() == outlineColor);
		}

		SECTION("line area is always 0")
		{
			REQUIRE(line.GetArea() == 0);
		}

		SECTION("line perimeter is calculated correctly using its length")
		{
			double expected = CPoint::Distance(start, end);
			REQUIRE(ApproximatelyEquals(line.GetPerimeter(), expected));
		}
	}

	SECTION("circle operations work correctly")
	{
		CPoint center(12, 3);
		double radius = 4;
		CCircle circle(center, radius, outlineColor, fillColor);

		SECTION("creating a circle saves its properties")
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

		SECTION("creating a rectangle saves its properties")
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

		SECTION("creating a triangle saves its properties")
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

TEST_CASE("shape processor works correctly")
{
	std::stringstream input;
	std::stringstream output;
	ShapeProcessor processor(input, output);

	SECTION("one figure is processed correctly")
	{
		SECTION("line segment")
		{
			input.str("line 20 10 12 34 00ff00\n");
			const std::string result = "\n[Largest area shape]\n"
									   "LINE SEGMENT\n"
									   "  start: (20.00, 10.00)\n"
									   "  end: (12.00, 34.00)\n"
									   "  outline: #00ff00\n"
									   "  area: 0.00\n"
									   "  perimeter: 25.30\n"
									   "\n[Smallest perimeter shape]\n"
									   "LINE SEGMENT\n"
									   "  start: (20.00, 10.00)\n"
									   "  end: (12.00, 34.00)\n"
									   "  outline: #00ff00\n"
									   "  area: 0.00\n"
									   "  perimeter: 25.30\n";
			processor.ProcessShapes();
			REQUIRE(output.str() == result);
		}

		SECTION("circle")
		{
			input.str("circle 20 10 34 00ff00 e5e5e5\n");
			const std::string result = "\n[Largest area shape]\n"
									   "CIRCLE\n"
									   "  center: (20.00, 10.00)\n"
									   "  radius: 34.00\n"
									   "  outline: #00ff00\n"
									   "  fill: #e5e5e5\n"
									   "  area: 3631.68\n"
									   "  perimeter: 213.63\n"
									   "\n[Smallest perimeter shape]\n"
									   "CIRCLE\n"
									   "  center: (20.00, 10.00)\n"
									   "  radius: 34.00\n"
									   "  outline: #00ff00\n"
									   "  fill: #e5e5e5\n"
									   "  area: 3631.68\n"
									   "  perimeter: 213.63\n";
			processor.ProcessShapes();
			REQUIRE(output.str() == result);
		}

		SECTION("rectangle")
		{
			input.str("rectangle 20 10 5 7 00ff00 e5e5e5\n");
			const std::string result = "\n[Largest area shape]\n"
									   "RECTANGLE\n"
									   "  top left: (20.00, 10.00)\n"
									   "  width: 5.00; height: 7.00\n"
									   "  outline: #00ff00\n"
									   "  fill: #e5e5e5\n"
									   "  area: 35.00\n"
									   "  perimeter: 24.00\n"
									   "\n[Smallest perimeter shape]\n"
									   "RECTANGLE\n"
									   "  top left: (20.00, 10.00)\n"
									   "  width: 5.00; height: 7.00\n"
									   "  outline: #00ff00\n"
									   "  fill: #e5e5e5\n"
									   "  area: 35.00\n"
									   "  perimeter: 24.00\n";
			processor.ProcessShapes();
			REQUIRE(output.str() == result);
		}

		SECTION("triangle")
		{
			input.str("triangle 20 10 5 7 13 6.5 00ff00 e5e5e5\n");
			const std::string result = "\n[Largest area shape]\n"
									   "TRIANGLE\n"
									   "  vertex1: (20.00, 10.00)\n"
									   "  vertex2: (5.00, 7.00)\n"
									   "  vertex3: (13.00, 6.50)\n"
									   "  outline: #00ff00\n"
									   "  fill: #e5e5e5\n"
									   "  area: 15.75\n"
									   "  perimeter: 31.14\n"
									   "\n[Smallest perimeter shape]\n"
									   "TRIANGLE\n"
									   "  vertex1: (20.00, 10.00)\n"
									   "  vertex2: (5.00, 7.00)\n"
									   "  vertex3: (13.00, 6.50)\n"
									   "  outline: #00ff00\n"
									   "  fill: #e5e5e5\n"
									   "  area: 15.75\n"
									   "  perimeter: 31.14\n";
			processor.ProcessShapes();
			REQUIRE(output.str() == result);
		}
	}
}
