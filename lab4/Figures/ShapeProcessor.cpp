#include "ShapeProcessor.h"

ShapeProcessor::ShapeProcessor(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void ShapeProcessor::ProcessShapes()
{
	auto const shapes = ReadShapes();
	if (shapes.empty())
	{
		throw std::invalid_argument("no shapes provided");
	}

	PrintShapeWithLargestArea(shapes);
	PrintShapeWithSmallestPerimeter(shapes);
}

ShapeProcessor::ShapeVector ShapeProcessor::ReadShapes()
{
	// TODO
	return {};
}

void ShapeProcessor::PrintShapeWithLargestArea(const ShapeProcessor::ShapeVector& shapes)
{
	auto const largestAreaShape = std::max_element(
		shapes.begin(),
		shapes.end(),
		[](const Shape& shape1, const Shape& shape2) {
			return shape1->GetArea() < shape2->GetArea();
		});
	PrintShapeInfo(*largestAreaShape);
}

void ShapeProcessor::PrintShapeWithSmallestPerimeter(const ShapeProcessor::ShapeVector& shapes)
{
	auto const smallestPerimeterShape = std::min_element(
		shapes.begin(),
		shapes.end(),
		[](const Shape& shape1, const Shape& shape2) {
			return shape1->GetPerimeter() < shape2->GetPerimeter();
		});
	PrintShapeInfo(*smallestPerimeterShape);
}

void ShapeProcessor::PrintShapeInfo(const Shape& shape)
{
	m_output << shape->ToString()
			 << "area: " << shape->GetArea() << '\n'
			 << "perimeter: " << shape->GetPerimeter() << '\n';
}
