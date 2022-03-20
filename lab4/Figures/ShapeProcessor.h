#pragma once

#include "Drawing/SFML/CCanvas.h"
#include "Point/CPoint.h"
#include "Shapes/IShape.h"
#include "Shapes/LineSegment/CLineSegment.h"
#include "Shapes/SolidShapes/Circle/CCircle.h"
#include "Shapes/SolidShapes/Rectangle/CRectangle.h"
#include "Shapes/SolidShapes/Triangle/CTriangle.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class ShapeProcessor
{
public:
	ShapeProcessor(std::istream& input, std::ostream& output);

	void ProcessShapes();

private:
	static constexpr int PRINT_PRECISION = 2;

	using Shape = std::unique_ptr<IShape>;
	using ShapeVector = std::vector<Shape>;

	enum class CommandType
	{
		IDLE,
		LINE,
		CIRCLE,
		RECTANGLE,
		TRIANGLE,
	};

	struct Command
	{
		CommandType type;
		std::string arguments;
	};

	using CommandHandler = std::function<Shape(const std::string& arguments)>;

	const std::map<std::string, CommandType> COMMAND_KEYWORDS = {
		{ "line", CommandType::LINE },
		{ "circle", CommandType::CIRCLE },
		{ "rectangle", CommandType::RECTANGLE },
		{ "triangle", CommandType::TRIANGLE },
	};

	ShapeVector ReadShapes();
	Command ReadCommand();
	CommandType ParseCommandType(const std::string& command);
	static CommandHandler GetHandlerForCommand(CommandType type);

	static Shape CreateLine(const std::string& arguments);
	static Shape CreateCircle(const std::string& arguments);
	static Shape CreateRectangle(const std::string& arguments);
	static Shape CreateTriangle(const std::string& arguments);

	static CPoint ReadPoint(std::istream& input);
	static uint32_t ReadColor(std::istream& input);
	static double ReadValue(std::istream& input);

	void PrintShapeWithLargestArea(const ShapeVector& shapes);
	void PrintShapeWithSmallestPerimeter(const ShapeVector& shapes);

	void PrintShapeInfo(const std::unique_ptr<IShape>& shape);

	static void Draw(const ShapeVector& shapes);

	std::istream& m_input;
	std::ostream& m_output;
};
