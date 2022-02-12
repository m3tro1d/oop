#include <fstream>
#include <iostream>
#include <optional>
#include <string>

// http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html
struct BMPInfo
{
	uint32_t width;
	uint32_t height;
	uint16_t bitsPerPixel;
	uint32_t imageSize;
};

const std::string BMP_SIGNATURE = "BM";
constexpr int WIDTH_BYTES_OFFSET = 18;
constexpr int WIDTH_BYTES_SIZE = 4;

std::optional<std::string> GetInputFilename(int argc, char** argv);
std::optional<BMPInfo> TryParseBMPFile(std::istream& input);

int main(int argc, char** argv)
{
	auto const inputFilename = GetInputFilename(argc, argv);
	if (!inputFilename)
	{
		std::cerr << "Invalid argument count\n"
				  << "Usage: bmpinfo.exe <input file name>\n";
		return EXIT_FAILURE;
	}

	std::ifstream inputFile(inputFilename.value(), std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open input file '" << inputFilename.value() << "' for reading\n";
		return EXIT_FAILURE;
	}

	auto const bmpInfo = TryParseBMPFile(inputFile);
	if (!bmpInfo)
	{
		std::cerr << "Input is not a valid BMP file\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

std::optional<std::string> GetInputFilename(int argc, char** argv)
{
	if (argc != 2)
	{
		return std::nullopt;
	}

	return argv[1];
}

bool IsBMPFile(std::istream& input)
{
	char signature[BMP_SIGNATURE.length() + 1];
	input.read(signature, static_cast<int>(BMP_SIGNATURE.length()));

	return signature == BMP_SIGNATURE;
}

std::optional<BMPInfo> TryParseBMPFile(std::istream& input)
{
	if (!IsBMPFile(input))
	{
		return std::nullopt;
	}

	BMPInfo info;
	input.seekg(WIDTH_BYTES_OFFSET, std::ios_base::beg);
	input.read((char*) &info.width, WIDTH_BYTES_SIZE);

	return info;
}
