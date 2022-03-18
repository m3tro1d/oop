#pragma once

#include "Shapes/IShape.h"
#include <iostream>
#include <memory>
#include <vector>

class ShapeProcessor
{
public:
	ShapeProcessor(std::istream& input, std::ostream& output);

	void ProcessShapes();

private:
	using Shape = std::unique_ptr<IShape>;
	using ShapeVector = std::vector<Shape>;

	ShapeVector ReadShapes();

	void PrintShapeWithLargestArea(const ShapeVector& shapes);
	void PrintShapeWithSmallestPerimeter(const ShapeVector& shapes);

	void PrintShapeInfo(const std::unique_ptr<IShape>& shape);

	std::istream& m_input;
	std::ostream& m_output;
};
