#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <algorithm>

constexpr int MIN_RADIX = 2;
constexpr int MAX_RADIX = 36;
constexpr int RADIX_NUMERAL_SYSTEM = 10;

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
				  << "Radix must be a number from " << MIN_RADIX << " to " << MAX_RADIX << "\n";
		return EXIT_FAILURE;
	}
	if (!args->destinationRadix)
	{
		std::cerr << "Invalid destination radix\n"
				  << "Radix must be a number from " << MIN_RADIX << " to " << MAX_RADIX << "\n";
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
	int radix = StringToInt(radixString, RADIX_NUMERAL_SYSTEM, wasError);
	if (wasError || radix < MIN_RADIX || radix > MAX_RADIX)
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

bool IsDigit(char ch)
{
	return '0' <= ch && ch <= '9';
}

bool IsUpperAlpha(char ch)
{
	return 'A' <= ch && ch <= 'Z';
}

int DigitToInt(char ch, int radix, bool& wasError)
{
	int value;

	if (IsDigit(ch))
	{
		value = ch - '0';

		if (value >= radix)
		{
			wasError = true;
			return -1;
		}

		return value;
	}

	if (!IsUpperAlpha(ch))
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

bool WillOverflowPositive(int number, int digit, int radix)
{
	return number > (std::numeric_limits<int>::max() - digit) / radix;
}

bool WillOverflowNegative(int number, int digit, int radix)
{
	return number < (std::numeric_limits<int>::min() + digit) / radix;
}

int AppendDigitToPositive(int number, int digit, int radix, bool& wasError)
{
	if (WillOverflowPositive(number, digit, radix))
	{
		wasError = true;
		return 0;
	}

	return number * radix + digit;
}

int AppendDigitToNegative(int number, int digit, int radix, bool& wasError)
{
	if (WillOverflowNegative(number, digit, radix))
	{
		wasError = true;
		return 0;
	}

	return number * radix - digit;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	if (str.length() == 0)
	{
		wasError = true;
		return 0;
	}

	bool isNegative = false;
	if (str[0] == '-')
	{
		isNegative = true;
	}

	int result = 0;
	size_t i = isNegative ? 1 : 0;
	for (; i < str.length(); ++i)
	{
		int digit = DigitToInt(str[i], radix, wasError);
		if (wasError)
		{
			return 0;
		}

		if (isNegative)
		{
			result = AppendDigitToNegative(result, digit, radix, wasError);
		}
		else
		{
			result = AppendDigitToPositive(result, digit, radix, wasError);
		}

		if (wasError)
		{
			return 0;
		}
	}

	return result;
}

char IntToDigit(int value, int radix, bool& wasError)
{
	if (value >= radix)
	{
		wasError = true;
		return '0';
	}

	if (0 <= value && value <= 9)
	{
		return static_cast<char>('0' + value);
	}

	if (10 <= value && value <= 36)
	{
		return static_cast<char>('A' + value - 10);
	}

	wasError = true;
	return '0';
}

std::string IntToString(int number, int radix, bool& wasError)
{
	std::string result;

	bool isNegative = false;
	if (number < 0)
	{
		isNegative = true;
	}

	while (number != 0)
	{
		int digit = std::abs(number % radix);
		result.push_back(IntToDigit(digit, radix, wasError));
		if (wasError)
		{
			return "";
		}

		number /= radix;
	}

	if (isNegative)
	{
		result.push_back('-');
	}
	std::reverse(result.begin(), result.end());

	return result;
}
