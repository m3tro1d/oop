#include <cmath>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

/*
 * http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html
 * https://en.wikipedia.org/wiki/BMP_file_format
 */

enum class CompressionMethod
{
	NONE,
	RLE8,
	RLE4,
	JPEG,
	PNG,
};

constexpr uint32_t COMPRESSION_NONE = 0;
constexpr uint32_t COMPRESSION_RLE8 = 1;
constexpr uint32_t COMPRESSION_RLE4 = 2;
constexpr uint32_t COMPRESSION_JPEG = 4;
constexpr uint32_t COMPRESSION_PNG = 5;

struct BMPInfo
{
	uint32_t width;
	uint32_t height;
	uint16_t bitsPerPixel;
	uint32_t imageSize;
	CompressionMethod compressionMethod;
};

const std::string BMP_SIGNATURE = "BM";
constexpr int WIDTH_BYTES_OFFSET = 18;
constexpr int HEIGHT_BYTES_OFFSET = 22;
constexpr int BITS_PER_PIXEL_OFFSET = 28;
constexpr int IMAGE_SIZE_OFFSET = 2;
constexpr int COMPRESSION_METHOD_OFFSET = 30;

constexpr int COLOR_PALETTE_BASE = 2;
constexpr uint16_t COLOR_PALETTE_THRESHOLD = 2;

std::optional<std::string> GetInputFilename(int argc, char** argv);
std::optional<BMPInfo> TryParseBMPFile(std::istream& input);
void PrintBMPInfo(const BMPInfo& info);

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

	if (inputFile.fail())
	{
		std::cerr << "Failed to read from input file\n";
		return EXIT_FAILURE;
	}

	PrintBMPInfo(bmpInfo.value());

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

void ReadBytes(std::istream& input, char* dist, int start, int n)
{
	input.seekg(start, std::ios_base::beg);
	input.read(dist, n);
}

bool IsBMPFile(std::istream& input)
{
	char signature[BMP_SIGNATURE.length() + 1];
	ReadBytes(input, signature, 0, static_cast<int>(BMP_SIGNATURE.length()));
	signature[2] = 0;

	return signature == BMP_SIGNATURE;
}

std::optional<CompressionMethod> ParseCompressionMethod(std::istream& input)
{
	uint32_t method;
	ReadBytes(input, reinterpret_cast<char*>(&method), COMPRESSION_METHOD_OFFSET, sizeof(method));

	switch (method)
	{
	case COMPRESSION_NONE:
		return CompressionMethod::NONE;
	case COMPRESSION_RLE8:
		return CompressionMethod::RLE8;
	case COMPRESSION_RLE4:
		return CompressionMethod::RLE4;
	case COMPRESSION_JPEG:
		return CompressionMethod::JPEG;
	case COMPRESSION_PNG:
		return CompressionMethod::PNG;
	default:
		return std::nullopt;
	}
}

std::optional<BMPInfo> TryParseBMPFile(std::istream& input)
{
	if (!IsBMPFile(input))
	{
		return std::nullopt;
	}

	BMPInfo info;
	ReadBytes(input, reinterpret_cast<char*>(&info.width), WIDTH_BYTES_OFFSET, sizeof(info.width));
	ReadBytes(input, reinterpret_cast<char*>(&info.height), HEIGHT_BYTES_OFFSET, sizeof(info.height));
	ReadBytes(input, reinterpret_cast<char*>(&info.bitsPerPixel), BITS_PER_PIXEL_OFFSET, sizeof(info.bitsPerPixel));
	// TODO: replace file size with actual image size (w/o headers)
	ReadBytes(input, reinterpret_cast<char*>(&info.imageSize), IMAGE_SIZE_OFFSET, sizeof(info.imageSize));

	auto const compressionMethod = ParseCompressionMethod(input);
	if (!compressionMethod)
	{
		return std::nullopt;
	}
	info.compressionMethod = compressionMethod.value();

	return info;
}

int GetColorsUsed(uint16_t bitsPerPixel)
{
	return static_cast<int>(std::pow(COLOR_PALETTE_BASE, bitsPerPixel));
}

std::string CompressionMethodToString(CompressionMethod method)
{
	switch (method)
	{
	case CompressionMethod::NONE:
		return "No compression";
	case CompressionMethod::RLE8:
		return "RLE 8-bit/pixel";
	case CompressionMethod::RLE4:
		return "RLE 4-bit/pixel";
	case CompressionMethod::JPEG:
		return "JPEG";
	case CompressionMethod::PNG:
		return "PNG";
	default:
		return "";
	}
}

void PrintBMPInfo(const BMPInfo& info)
{
	std::cout << "Resolution: " << info.width << 'x' << info.height << '\n'
			  << "Bits per pixel: " << info.bitsPerPixel << '\n';

	if (info.bitsPerPixel >= COLOR_PALETTE_THRESHOLD)
	{
		std::cout << "Colors used: " << GetColorsUsed(info.bitsPerPixel) << '\n';
	}
	else
	{
		std::cout << "The image is monochrome\n";
	}

	std::cout << "Image size: " << info.imageSize << " bytes\n"
			  << "Compression method: " << CompressionMethodToString(info.compressionMethod) << '\n';
}
