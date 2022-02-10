#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFilename;
	std::string outputFilename;
};

constexpr size_t FIELD_SIZE = 100;
using Field = std::array<std::array<char, FIELD_SIZE>, FIELD_SIZE>;

constexpr char EMPTY_CELL = ' ';
constexpr char CONTOUR_CELL = '#';
constexpr char MARKER_CELL = 'O';
constexpr char FILLED_CELL = '.';

std::optional<Args> ParseArgs(int argc, char** argv);
std::optional<Field> ReadField(std::istream& input, bool& markerOccurred);
void PrintField(std::ostream& output, Field field);

int main(int argc, char** argv)
{
	auto const args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cerr << "Invalid argument count\n"
				  << "Usage: fill.exe <input file> <output file>\n";
		return EXIT_FAILURE;
	}

	std::ifstream inputFile;
	inputFile.open(args->inputFilename);
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open input file '" << args->inputFilename << "' for reading\n";
		return EXIT_FAILURE;
	}

	std::ofstream outputFile;
	outputFile.open(args->outputFilename);
	if (!outputFile.is_open())
	{
		std::cerr << "Failed to open output file '" << args->outputFilename << "' for writing\n";
		return EXIT_FAILURE;
	}

	bool markerOccurred;
	auto field = ReadField(inputFile, markerOccurred);
	if (!field)
	{
		std::cerr << "Invalid matrix format\n";
		return EXIT_FAILURE;
	}
	if (!markerOccurred)
	{
		std::cerr << "There is no markers - nothing to fill!\n";
		return EXIT_FAILURE;
	}
	if (inputFile.bad())
	{
		std::cerr << "Failed to read from input file\n";
		return EXIT_FAILURE;
	}

	// TODO: fill

	PrintField(outputFile, field.value());

	if (!outputFile.flush())
	{
		std::cerr << "Failed to write to output file\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc != 3)
	{
		return std::nullopt;
	}

	Args args;
	args.inputFilename = argv[1];
	args.outputFilename = argv[2];

	return args;
}

std::optional<Field> ReadField(std::istream& input, bool& markerOccurred)
{
	char ch;
	size_t row = 0;
	size_t column = 0;
	Field result;

	while (!input.eof())
	{
		input.get(ch);

		switch (ch)
		{
		case MARKER_CELL:
			markerOccurred = true;
			// fallthrough
		case EMPTY_CELL:
		case CONTOUR_CELL:
			result[row][column++] = ch;
			break;
		case '\n':
			row++;
			column = 0;
			break;
		default:
			return std::nullopt;
		}

		if (row == FIELD_SIZE - 1 && column == FIELD_SIZE)
		{
			break;
		}
	}

	return result;
}

void PrintField(std::ostream& output, Field field)
{
	for (size_t row = 0; row < FIELD_SIZE; ++row)
	{
		for (size_t column = 0; column < FIELD_SIZE; ++column)
		{
			output << field[row][column];
		}
		output << '\n';
	}
}
