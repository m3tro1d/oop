#include "ShapeProcessor.h"
#include "Shapes/LineSegment/CLineSegment.h"

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
	ShapeVector result;
	while (!m_input.eof())
	{
		auto const command = ReadCommand();
		auto shape = GetHandlerForCommand(command.type)(command.arguments);
		if (shape)
		{
			result.push_back(std::move(shape));
		}
	}

	return result;
}

ShapeProcessor::Command ShapeProcessor::ReadCommand()
{
	std::string userInput;
	std::string arguments;
	std::getline(m_input, userInput);
	if (userInput.empty())
	{
		return {
			.type = CommandType::IDLE,
		};
	}

	std::stringstream input(userInput);
	CommandType type;
	std::string commandTypeStr;
	std::getline(input, commandTypeStr, ' ');
	if (!std::getline(input, arguments))
	{
		throw std::invalid_argument("no arguments provided");
	}
	type = ParseCommandType(commandTypeStr);

	return {
		.type = type,
		.arguments = arguments,
	};
}

ShapeProcessor::CommandType ShapeProcessor::ParseCommandType(const std::string& command)
{
	auto const type = COMMAND_KEYWORDS.find(command);
	if (type == COMMAND_KEYWORDS.end())
	{
		throw std::invalid_argument("invalid command");
	}

	return type->second;
}

ShapeProcessor::CommandHandler ShapeProcessor::GetHandlerForCommand(ShapeProcessor::CommandType type)
{
	switch (type)
	{
	case CommandType::LINE:
		return [](const std::string& arguments) {
			return CreateLine(arguments);
		};
	case CommandType::CIRCLE:
		return [](const std::string& arguments) {
			return CreateCircle(arguments);
		};
	case CommandType::RECTANGLE:
		return [](const std::string& arguments) {
			return CreateRectangle(arguments);
		};
	case CommandType::TRIANGLE:
		return [](const std::string& arguments) {
			return CreateTriangle(arguments);
		};
	default:
		return [](const std::string&) {
			return nullptr;
		};
	}
}

ShapeProcessor::Shape ShapeProcessor::CreateLine(const std::string& arguments)
{
	std::stringstream input(arguments);
	auto const start = ReadPoint(input);
	auto const end = ReadPoint(input);
	auto const outlineColor = ReadColor(input);

	return std::make_unique<CLineSegment>(start, end, outlineColor);
}

ShapeProcessor::Shape ShapeProcessor::CreateCircle(const std::string& arguments)
{
	std::stringstream input(arguments);
	auto const center = ReadPoint(input);
	auto const radius = ReadValue(input);
	auto const outlineColor = ReadColor(input);
	auto const fillColor = ReadColor(input);

	return std::make_unique<CCircle>(center, radius, outlineColor, fillColor);
}

ShapeProcessor::Shape ShapeProcessor::CreateRectangle(const std::string& arguments)
{
	std::stringstream input(arguments);
	auto const topLeft = ReadPoint(input);
	auto const width = ReadValue(input);
	auto const height = ReadValue(input);
	auto const outlineColor = ReadColor(input);
	auto const fillColor = ReadColor(input);

	return std::make_unique<CRectangle>(topLeft, width, height, outlineColor, fillColor);
}

ShapeProcessor::Shape ShapeProcessor::CreateTriangle(const std::string& arguments)
{
	std::stringstream input(arguments);
	auto const vertex1 = ReadPoint(input);
	auto const vertex2 = ReadPoint(input);
	auto const vertex3 = ReadPoint(input);
	auto const outlineColor = ReadColor(input);
	auto const fillColor = ReadColor(input);

	return std::make_unique<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}

CPoint ShapeProcessor::ReadPoint(std::istream& input)
{
	double x = ReadValue(input);
	double y = ReadValue(input);

	return { x, y };
}

uint32_t ShapeProcessor::ReadColor(std::istream& input)
{
	uint32_t value;

	if (!(input >> std::hex >> value))
	{
		throw std::invalid_argument("invalid arguments");
	}

	return value;
}

double ShapeProcessor::ReadValue(std::istream& input)
{
	double value;

	if (!(input >> value))
	{
		throw std::invalid_argument("invalid arguments");
	}

	return value;
}

void ShapeProcessor::PrintShapeWithLargestArea(const ShapeProcessor::ShapeVector& shapes)
{
	auto const largestAreaShape = std::max_element(
		shapes.begin(),
		shapes.end(),
		[](const Shape& shape1, const Shape& shape2) {
			return shape1->GetArea() < shape2->GetArea();
		});

	m_output << "\n[Largest area shape]\n";
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

	m_output << "\n[Smallest perimeter shape]\n";
	PrintShapeInfo(*smallestPerimeterShape);
}

void ShapeProcessor::PrintShapeInfo(const Shape& shape)
{
	m_output << std::fixed << std::setprecision(PRINT_PRECISION)
			 << shape->ToString()
			 << "  area: " << shape->GetArea() << '\n'
			 << "  perimeter: " << shape->GetPerimeter() << '\n';
}
