#include <iostream>
#include <optional>
#include <string>
#include <cmath>
#include <cctype>

constexpr int MIN_RADIX = 2;
constexpr int MAX_RADIX = 36;

struct Args
{
	std::string number;
	std::optional<int> sourceRadix;
	std::optional<int> destinationRadix;
};

std::optional<Args> ParseArgs(int argc, char** argv);
int StringToInt(const std::string& str, int radix, bool& wasError);
std::string IntToString(int n, int radix, bool& wasError);

int main(int argc, char** argv)
{
	auto const args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cerr << "Invalid argument count\n"
				  << "Usage: radix.exe <number> <source radix> <destination radix>\n";
		return EXIT_FAILURE;
	}
	if (!args->sourceRadix)
	{
		std::cerr << "Invalid source radix\n"
				  << "Radix must be a number from 2 to 36\n";
		return EXIT_FAILURE;
	}
	if (!args->destinationRadix)
	{
		std::cerr << "Invalid destination radix\n"
				  << "Radix must be a number from 2 to 36\n";
		return EXIT_FAILURE;
	}

	bool wasError;
	int const sourceRadix = args->sourceRadix.value();
	int const destinationRadix = args->destinationRadix.value();
	
	int number = StringToInt(args->number, sourceRadix, wasError);
	if (wasError)
	{
		std::cerr << "Error while converting number from source radix\n";
		return EXIT_FAILURE;
	}

	std::string result = IntToString(number, destinationRadix, wasError);
	if (wasError)
	{
		std::cerr << "Error while converting number to destination radix\n";
		return EXIT_FAILURE;
	}

	std::printf("%s (%d) = %s (%d)\n", args->number.c_str(), sourceRadix, result.c_str(), destinationRadix);

	return EXIT_SUCCESS;
}

std::optional<int> ParseRadix(const std::string& radixString)
{
	bool wasError;
	int radix = StringToInt(radixString, 10, wasError);
	if (wasError)
	{
		return std::nullopt;
	}

	if (radix < MIN_RADIX || radix > MAX_RADIX)
	{
		return std::nullopt;
	}

	return radix;
}

std::optional<Args> ParseArgs(int argc, char** argv)
{
	if (argc != 4)
	{
		return std::nullopt;
	}

	Args args;
	args.number = argv[1];
	args.sourceRadix = ParseRadix(argv[2]);
	args.destinationRadix = ParseRadix(argv[3]);

	return args;
}

int DigitToInt(char ch, int radix, bool& wasError)
{
	int value;

	if (std::isdigit(ch))
	{
		value = ch - '0';

		if (value >= radix)
		{
			wasError = true;
			return -1;
		}

		return value;
	}

	if (!(std::isalpha(ch) || std::isupper(ch)))
	{
		wasError = true;
		return -1;
	}

	value = ch - 'A' + 10;
	if (value >= radix)
	{
		wasError = true;
		return -1;
	}

	return value;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	int result = 0;

	for (int i = str.length() - 1; i >= 0; --i)
	{
		size_t position = str.length() - i - 1;

		int value = DigitToInt(str.at(i), radix, wasError);
		if (wasError)
		{
			return -1;
		}

		result += value * std::pow(radix, position);
	}

	return result;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	return std::to_string(n);
}
