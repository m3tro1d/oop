#include <fstream>
#include <iostream>
#include <optional>
#include <string>

enum class Mode
{
	CRYPT,
	DECRYPT,
};

struct Args
{
	Mode mode;
	std::string inputFilename;
	std::string outputFilename;
	int key;
};

const std::string MODE_CRYPT = "crypt";
const std::string MODE_DECRYPT = "decrypt";
constexpr int MIN_KEY = 0;
constexpr int MAX_KEY = 255;

using Byte = char;

std::optional<Args> ParseArgs(int argc, char** argv);
void InitializeFiles(std::ifstream& inputFile, std::ofstream& outputFile, const Args& args);
void Encrypt(std::istream& input, std::ostream& output, int key);
void Decrypt(std::istream& input, std::ostream& output, int key);

int main(int argc, char** argv)
{
	auto const args = ParseArgs(argc, argv);
	if (!args.has_value())
	{
		return EXIT_FAILURE;
	}

	try
	{
		std::ifstream inputFile;
		std::ofstream outputFile;
		InitializeFiles(inputFile, outputFile, args.value());

		switch (args->mode)
		{
		case Mode::CRYPT:
			Encrypt(inputFile, outputFile, args->key);
			break;
		case Mode::DECRYPT:
			Decrypt(inputFile, outputFile, args->key);
			break;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

std::optional<Mode> ParseMode(const std::string& mode)
{
	if (mode == MODE_CRYPT)
	{
		return Mode::CRYPT;
	}
	else if (mode == MODE_DECRYPT)
	{
		return Mode::DECRYPT;
	}

	std::cerr << "Invalid mode: should be either '" << MODE_CRYPT << "' or '" << MODE_DECRYPT << "'\n";
	return std::nullopt;
}

std::optional<int> ParseKey(const std::string& key)
{
	int keyValue;
	try
	{
		keyValue = std::stoi(key);
	}
	catch (const std::exception&)
	{
		std::cerr << "Invalid key\n";
		return std::nullopt;
	}

	if (keyValue < MIN_KEY || keyValue > MAX_KEY)
	{
		std::cerr << "Key should have value from " << MIN_KEY << " to " << MAX_KEY << '\n';
		return std::nullopt;
	}

	return keyValue;
}

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc != 5)
	{
		std::cerr << "Invalid argument count\n"
				  << "Usage: crypt.exe <crypt | decrypt> <input file> <output file> <key>\n";
		return std::nullopt;
	}

	Args args;
	auto const mode = ParseMode(argv[1]);
	if (!mode.has_value())
	{
		return std::nullopt;
	}
	args.mode = mode.value();

	args.inputFilename = argv[2];
	args.outputFilename = argv[3];

	auto const key = ParseKey(argv[4]);
	if (!key.has_value())
	{
		return std::nullopt;
	}
	args.key = key.value();

	return args;
}

void InitializeFiles(std::ifstream& inputFile, std::ofstream& outputFile, const Args& args)
{
	inputFile.open(args.inputFilename, std::ios::in | std::ios::binary);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open input file for reading");
	}

	outputFile.open(args.outputFilename, std::ios::out | std::ios::binary);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open output file for writing");
	}
}

void Encrypt(std::istream& input, std::ostream& output, int key)
{
	Byte byte;
	while (input.read(&byte, sizeof(byte)))
	{
		output.write(&byte, sizeof(byte));
	}

	if (input.bad())
	{
		throw std::runtime_error("Failed to read from input file");
	}
	if (!output.flush())
	{
		throw std::runtime_error("Failed to write to output file");
	}
}

void Decrypt(std::istream& input, std::ostream& output, int key)
{
	Byte byte;
	while (input.read(&byte, sizeof(byte)))
	{
		output.write(&byte, sizeof(byte));
	}

	if (!input.bad())
	{
		throw std::runtime_error("Failed to read from input file");
	}
	if (!output.flush())
	{
		throw std::runtime_error("Failed to write to output file");
	}
}
