#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>

constexpr int PRECISION = 3;
constexpr int WIDTH = 6;

constexpr size_t MATRIX_SIZE = 3;
using Matrix = std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>;

std::optional<std::string> GetMatrixFilename(int argc, char** argv);
std::optional<Matrix> ReadMatrix(std::istream& input);
std::optional<Matrix> InvertMatrix(Matrix matrix);
void PrintMatrix(Matrix matrix);

int main(int argc, char** argv)
{
	auto const matrixFilename = GetMatrixFilename(argc, argv);
	if (!matrixFilename)
	{
		std::cerr << "Invalid argument count"
				  << "Usage: invert.exe <matrix file>\n";
		return EXIT_FAILURE;
	}

	std::ifstream matrixFile;
	matrixFile.open(matrixFilename.value());
	if (!matrixFile.is_open())
	{
		std::cerr << "Failed to open matrix file '" << matrixFilename.value() << "' for reading\n";
		return EXIT_FAILURE;
	}

	auto const matrix = ReadMatrix(matrixFile);
	if (!matrix)
	{
		std::cerr << "Invalid matrix format\n";
		return EXIT_FAILURE;
	}

	if (matrixFile.bad())
	{
		std::cerr << "Failed to read from matrix file\n";
		return EXIT_FAILURE;
	}

	auto const inverseMatrix = InvertMatrix(matrix.value());
	if (!inverseMatrix)
	{
		std::cerr << "Matrix can not be inverted\n";
		return EXIT_FAILURE;
	}

	PrintMatrix(inverseMatrix.value());

	return EXIT_SUCCESS;
}

std::optional<std::string> GetMatrixFilename(int argc, char** argv)
{
	if (argc != 2)
	{
		return std::nullopt;
	}

	return argv[1];
}

std::optional<Matrix> ReadMatrix(std::istream& input)
{
	Matrix result;

	for (size_t row = 0; row < MATRIX_SIZE; ++row)
	{
		for (size_t column = 0; column < MATRIX_SIZE; ++column)
		{
			if (!(input >> result[row][column]))
			{
				return std::nullopt;
			}
		}
	}

	return result;
}

Matrix GetAdjacentMatrix(const Matrix matrix, size_t matrixSize, size_t removedRow, size_t removedColumn)
{
	Matrix result;
	if (matrixSize == 1)
	{
		return matrix;
	}

	size_t newRow = 0;
	size_t newColumn = 0;
	for (size_t row = 0; row < matrixSize; ++row)
	{
		for (size_t column = 0; column < matrixSize; ++column)
		{
			if (row != removedRow && column != removedColumn)
			{
				result[newRow][newColumn++] = matrix[row][column];
				if (newColumn == matrixSize - 1)
				{
					newColumn = 0;
					++newRow;
				}
			}
		}
	}

	return result;
}

double CalculateDeterminant(const Matrix matrix, size_t matrixSize)
{
	if (matrixSize == 1)
	{
		return matrix[0][0];
	}

	double result = 0;
	for (size_t column = 0; column < matrixSize; ++column)
	{
		Matrix const minorMatrix = GetAdjacentMatrix(matrix, matrixSize, 0, column);
		double const minor = CalculateDeterminant(minorMatrix, matrixSize - 1);
		if (column % 2)
		{
			result -= matrix[0][column] * minor;
		}
		else
		{
			result += matrix[0][column] * minor;
		}
	}

	return result;
}

bool IsZero(double value)
{
	return std::abs(value) < std::numeric_limits<double>::epsilon();
}

std::optional<Matrix> InvertMatrix(const Matrix matrix)
{
	double determinant = CalculateDeterminant(matrix, MATRIX_SIZE);
	std::cout << determinant << std::endl;
	if (IsZero(determinant))
	{
		return std::nullopt;
	}

	return std::nullopt;
}

void PrintMatrix(const Matrix matrix)
{
	std::cout << std::fixed << std::setprecision(PRECISION);
	for (size_t row = 0; row < MATRIX_SIZE; ++row)
	{
		for (size_t column = 0; column < MATRIX_SIZE; ++column)
		{
			std::cout << ' ' << std::setw(WIDTH) << matrix[row][column];
		}

		std::cout << '\n';
	}
}
