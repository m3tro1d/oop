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
void InitializeFiles(std::ifstream& inputFile, std::ofstream& outputFile, const Args& args);
Field ReadField(std::istream& input);
void FillField(Field& field);
void PrintField(std::ostream& output, const Field& field);

int main(int argc, char** argv)
{
	auto const args = ParseArgs(argc, argv);
	if (!args.has_value())
	{
		std::cerr << "Invalid argument count\n"
				  << "Usage: fill.exe <input file> <output file>\n";
		return EXIT_FAILURE;
	}

	try
	{
		std::ifstream inputFile;
		std::ofstream outputFile;
		InitializeFiles(inputFile, outputFile, args.value());

		Field field = ReadField(inputFile);
		FillField(field);
		PrintField(outputFile, field);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
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

void InitializeFiles(std::ifstream& inputFile, std::ofstream& outputFile, const Args& args)
{
	inputFile.open(args.inputFilename);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open input file for reading");
	}

	outputFile.open(args.outputFilename);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open output file for writing");
	}
}

Field ReadField(std::istream& input)
{
	char ch;
	size_t row = 0;
	size_t column = 0;
	Field result;
	std::fill(&result[0][0], &result[FIELD_SIZE - 1][FIELD_SIZE], EMPTY_CELL);
	bool markerOccurred = false;

	while (!input.eof())
	{
		input.get(ch);

		if (ch == MARKER_CELL)
		{
			markerOccurred = true;
		}

		switch (ch)
		{
		case MARKER_CELL:
		case EMPTY_CELL:
		case CONTOUR_CELL:
			result[row][column++] = ch;
			break;
		case '\n':
			row++;
			column = 0;
			break;
		default:
			throw std::invalid_argument("Invalid field format");
		}

		if (column == FIELD_SIZE - 1)
		{
			column = 0;
			input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (row == FIELD_SIZE - 1)
		{
			break;
		}
	}

	if (!markerOccurred)
	{
		throw std::logic_error("There is no markers - nothing to fill!");
	}
	if (input.bad())
	{
		throw std::runtime_error("Failed to read from input file");
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

	if (!output.flush())
	{
		throw std::runtime_error("Failed to write to output file");
	}
}
