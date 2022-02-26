#define CATCH_CONFIG_MAIN
#include "../DictionaryConsoleLib.h"
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
			std::stringstream input("The Red Square:Красная Площадь\ncat:кот, кошка\n");
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
		SECTION("saving empty dictionary results in an empty file")
		{
			std::stringstream output;
			Dictionary dictionary;
			WriteDictionaryFile(output, dictionary);

			REQUIRE(output.str().empty());
		}

		SECTION("saving populated dictionary works correctly")
		{
			std::stringstream output;
			Dictionary dictionary;
			AddTranslation(dictionary, "cat", "кот, кошка");
			AddTranslation(dictionary, "The Red Square", "Красная Площадь");
			WriteDictionaryFile(output, dictionary);

			REQUIRE(output.str() == "cat:кот, кошка\nthe red square:Красная Площадь\n");
		}
	}
}

TEST_CASE("dictionary manipulations are working correctly")
{
	SECTION("adding translations works correctly")
	{
		Dictionary dictionary;
		std::string const source = "cat";
		std::string const translation = "кот, кошка";
		AddTranslation(dictionary, source, translation);

		REQUIRE(dictionary.size() == 1);
		REQUIRE(dictionary[source] == translation);
	}

	SECTION("looking up an existing source returns its translation")
	{
		Dictionary dictionary;
		std::string const source = "cat";
		std::string const translation = "кот, кошка";
		AddTranslation(dictionary, source, translation);
		auto const lookedUp = LookupTranslation(dictionary, source);

		REQUIRE(lookedUp.has_value());
		REQUIRE(lookedUp.value() == translation);
	}

	SECTION("looking up non existing source returns empty translation")
	{
		Dictionary dictionary;
		auto const lookedUp = LookupTranslation(dictionary, "cat");

		REQUIRE(!lookedUp.has_value());
	}

	SECTION("source search works case-insensitively, but translations case is preserved")
	{
		Dictionary dictionary;
		std::string const source = "cat";
		std::string const translation = "кот, кошка";
		AddTranslation(dictionary, source, translation);
		auto const lookedUp = LookupTranslation(dictionary, "CaT");

		REQUIRE(lookedUp.has_value());
		REQUIRE(lookedUp == translation);
	}
}

TEST_CASE("user interactions work correctly")
{
	// TODO
}
