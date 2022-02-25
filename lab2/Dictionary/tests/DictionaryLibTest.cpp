#define CATCH_CONFIG_MAIN
#include "../DictionaryLib.h"
#include "catch.hpp"

TEST_CASE("dictionary file operations work correctly")
{
	SECTION("dictionary file path is determined correctly")
	{
		SECTION("dictionary file path grabs value from the arguments if they are present")
		{
			int const argc = 2;
			char** argv = new char*[2];
			argv[1] = new char[10];
			std::strcpy(argv[1], "test.txt");
			auto const dictionaryPath = GetDictionaryPath(argc, argv);
			delete[] argv[1];
			delete[] argv;

			REQUIRE(dictionaryPath == "test.txt");
		}

		SECTION("dictionary file path fallbacks to the default value if incorrect arguments were provided")
		{
			int const argc = 1;
			auto const dictionaryPath = GetDictionaryPath(argc, nullptr);

			REQUIRE(dictionaryPath == DEFAULT_DICTIONARY_PATH);
		}
	}

	SECTION("dictionary file initial parsing works correctly")
	{
		SECTION("empty file results in an empty array")
		{
			std::stringstream input("\n");
			Dictionary dictionary;
			ReadDictionaryFile(input, dictionary);

			REQUIRE(dictionary.empty());
		}

		SECTION("valid translations are parsed correctly")
		{
			std::stringstream input("cat:кот, кошка\nThe Red Square:Красная Площадь\n");
			Dictionary dictionary;
			ReadDictionaryFile(input, dictionary);

			REQUIRE(dictionary.size() == 2);
			REQUIRE(dictionary["cat"] == "кот, кошка");
			REQUIRE(dictionary["The Red Square"] == "Красная Площадь");
		}

		SECTION("invalid translation file results in an exception")
		{
			std::stringstream input;
			Dictionary dictionary;

			input.str(":кот, кошка\n");
			REQUIRE_THROWS_AS(ReadDictionaryFile(input, dictionary), std::invalid_argument);

			input.str("cat:\n");
			REQUIRE_THROWS_AS(ReadDictionaryFile(input, dictionary), std::invalid_argument);

			input.str("whatever\n");
			REQUIRE_THROWS_AS(ReadDictionaryFile(input, dictionary), std::invalid_argument);

			input.str(":\n");
			REQUIRE_THROWS_AS(ReadDictionaryFile(input, dictionary), std::invalid_argument);
		}
	}

	SECTION("dictionary file saving works correctly")
	{
		// TODO
	}
}
