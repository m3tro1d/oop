#include "FindMaxEx.hpp"

struct Sportsman
{
	std::string firstName;
	std::string lastName;
	std::string patronymic;
	int height;
	int weight;
};

Sportsman FindSportsmanWithMaxHeight(std::vector<Sportsman> const& sportsmen);
Sportsman FindSportsmanWithMaxWeight(std::vector<Sportsman> const& sportsmen);

int main()
{
	// TODO
	return EXIT_SUCCESS;
}

Sportsman FindSportsmanWithMaxHeight(std::vector<Sportsman> const& sportsmen)
{
	Sportsman result;
	auto isEmpty = !FindMaxEx(sportsmen, result, [](Sportsman const& s1, Sportsman const& s2) {
		return s1.height < s2.height;
	});

	if (isEmpty)
	{
		throw std::invalid_argument("no sportsmen provided");
	}

	return result;
}

Sportsman FindSportsmanWithMaxWeight(std::vector<Sportsman> const& sportsmen)
{
	Sportsman result;
	auto isEmpty = !FindMaxEx(sportsmen, result, [](Sportsman const& s1, Sportsman const& s2) {
		return s1.weight < s2.weight;
	});

	if (isEmpty)
	{
		throw std::invalid_argument("no sportsmen provided");
	}

	return result;
}
