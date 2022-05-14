#include "FindMaxEx.hpp"

#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>

struct Sportsman
{
	std::string firstName;
	std::string lastName;
	std::string patronymic;

	int height = 0;
	int weight = 0;
};

std::optional<std::string> GetSportsmenFilename(int argc, char** argv);
void InitializeFile(std::ifstream& file, std::string const& filename);
std::vector<Sportsman> ParseSportsmen(std::istream& input);
Sportsman FindTallestSportsman(std::vector<Sportsman> const& sportsmen);
Sportsman FindHeaviestSportsman(std::vector<Sportsman> const& sportsmen);
void PrintSportsman(std::ostream& output, Sportsman const& sportsman);

int main(int argc, char** argv)
{
	auto const sportsmenFilename = GetSportsmenFilename(argc, argv);
	if (!sportsmenFilename)
	{
		std::cerr << "Invalid argument count\n"
				  << "Usage: FindMaxEx.exe <sportsmen file>\n";
		return EXIT_FAILURE;
	}

	try
	{
		std::ifstream sportsmenFile;
		InitializeFile(sportsmenFile, sportsmenFilename.value());
		auto const sportsmen = ParseSportsmen(sportsmenFile);

		auto const tallestSportsman = FindTallestSportsman(sportsmen);
		auto const heaviestSportsman = FindHeaviestSportsman(sportsmen);

		std::cout << "[Tallest Sportsman]\n";
		PrintSportsman(std::cout, tallestSportsman);
		std::cout << "\n[Heaviest Sportsman]\n";
		PrintSportsman(std::cout, heaviestSportsman);
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

std::optional<std::string> GetSportsmenFilename(int argc, char** argv)
{
	if (argc != 2)
	{
		return std::nullopt;
	}

	return argv[1];
}

void InitializeFile(std::ifstream& file, std::string const& filename)
{
	file.open(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("failed to open input file for reading");
	}
}

std::vector<Sportsman> ParseSportsmen(std::istream& input)
{
	std::vector<Sportsman> result;

	std::string line;
	while (std::getline(input, line))
	{
		std::stringstream lineStream(line);
		Sportsman sportsman;
		lineStream >> sportsman.lastName >> sportsman.firstName >> sportsman.patronymic
			>> sportsman.height
			>> sportsman.weight;

		if (lineStream.bad())
		{
			throw std::runtime_error("invalid sportsmen file format");
		}

		result.push_back(std::move(sportsman));
	}

	return result;
}

Sportsman FindTallestSportsman(std::vector<Sportsman> const& sportsmen)
{
	Sportsman result;
	auto isEmpty = !FindMaxEx(
		sportsmen,
		result,
		[](Sportsman const& s1, Sportsman const& s2) {
			return s1.height < s2.height;
		});

	if (isEmpty)
	{
		throw std::invalid_argument("no sportsmen provided");
	}

	return result;
}

Sportsman FindHeaviestSportsman(std::vector<Sportsman> const& sportsmen)
{
	Sportsman result;
	auto isEmpty = !FindMaxEx(
		sportsmen,
		result,
		[](Sportsman const& s1, Sportsman const& s2) {
			return s1.weight < s2.weight;
		});

	if (isEmpty)
	{
		throw std::invalid_argument("no sportsmen provided");
	}

	return result;
}

void PrintSportsman(std::ostream& output, Sportsman const& sportsman)
{
	output << sportsman.lastName << " " << sportsman.firstName << " " << sportsman.patronymic << "\n"
		   << "Height: " << sportsman.height << "\n"
		   << "Weight: " << sportsman.weight << "\n";
}
