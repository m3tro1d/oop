#include <array>
#include <fstream>
#include <iostream>
#include <optional>

using Matrix = std::array<std::array<double, 3>, 3>;

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
	// TODO
	return std::nullopt;
}

std::optional<Matrix> InvertMatrix(const Matrix matrix)
{
	// TODO: 1. Find determinant
	//       2. Find cofactor matrix
	//       Both functions can be general for matrices of all sizes
	return std::nullopt;
}

void PrintMatrix(const Matrix matrix)
{
	// TODO
}
