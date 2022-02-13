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
void FillField(Field& field);
void PrintField(std::ostream& output, const Field& field);

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
		std::cerr << "Invalid field format\n";
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

	FillField(field.value());

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
	std::fill(&result[0][0], &result[FIELD_SIZE - 1][FIELD_SIZE], EMPTY_CELL);
	markerOccurred = false;

	while (!input.eof())
	{
		input.get(ch);

		switch (ch)
		{
		case MARKER_CELL:
			markerOccurred = true;
			[[fallthrough]];
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

		if (column == FIELD_SIZE - 1)
		{
			column = 0;
			input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (row == FIELD_SIZE - 1)
			{
				break;
			}
		}
	}

	return result;
}

void FillCell(Field& field, size_t row, size_t column)
{
	char& cell = field[row][column];
	if (cell == EMPTY_CELL || cell == MARKER_CELL)
	{
		if (cell == EMPTY_CELL)
		{
			cell = FILLED_CELL;
		}

		if (column > 0)
		{
			FillCell(field, row, column - 1);
		}

		if (row > 0)
		{
			FillCell(field, row - 1, column);
		}

		if (column < FIELD_SIZE - 1)
		{
			FillCell(field, row, column + 1);
		}

		if (row < FIELD_SIZE - 1)
		{
			FillCell(field, row + 1, column);
		}
	}
}

void FillField(Field& field)
{
	for (size_t row = 0; row < FIELD_SIZE; ++row)
	{
		for (size_t column = 0; column < FIELD_SIZE; ++column)
		{
			if (field[row][column] == MARKER_CELL)
			{
				FillCell(field, row, column);
			}
		}
	}
}

void PrintField(std::ostream& output, const Field& field)
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
