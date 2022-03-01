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
		SECTION("empty file results in an empty dictionary")
		{
			std::stringstream input;
			Dictionary dictionary;

			input.str("");
			ReadDictionaryFile(input, dictionary);
			REQUIRE(dictionary.empty());

			input.str("\n");
			ReadDictionaryFile(input, dictionary);
			REQUIRE(dictionary.empty());
		}

		SECTION("valid translations are parsed correctly")
		{
			std::stringstream input("the red square\nКрасная Площадь\ncat\nкот, кошка\n");
			Dictionary dictionary;
			ReadDictionaryFile(input, dictionary);

			REQUIRE(dictionary.size() == 2);
			REQUIRE(dictionary["cat"] == std::set<std::string>{ "кот", "кошка" });
			REQUIRE(dictionary["the red square"] == std::set<std::string>{ "Красная Площадь" });
		}

		SECTION("invalid translation file results in an exception")
		{
			std::stringstream input("\ncat\n");
			Dictionary dictionary;

			REQUIRE_THROWS_AS(ReadDictionaryFile(input, dictionary), std::invalid_argument);
		}

		SECTION("parsing doesn't rely on special separators")
		{
			std::istringstream input("cat:\n:кисулькен\n");
			Dictionary dictionary;
			ReadDictionaryFile(input, dictionary);

			REQUIRE(dictionary.size() == 1);
			REQUIRE(dictionary["cat:"] == std::set<std::string>{ ":кисулькен" });
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
			AddTranslations(dictionary, "cat", "кот, кошка");
			AddTranslations(dictionary, "The Red Square", "Красная Площадь");
			WriteDictionaryFile(output, dictionary);

			REQUIRE(output.str() == "cat\nкот, кошка\nthe red square\nКрасная Площадь\n");
		}
	}
}

TEST_CASE("dictionary manipulations are working correctly")
{
	SECTION("adding translations works correctly")
	{
		SECTION("adding one translation works correctly")
		{
			Dictionary dictionary;
			std::string const source = "cat";
			std::string const translationsString = "кот";
			std::set<std::string> const translations = { "кот" };
			AddTranslations(dictionary, source, translationsString);

			REQUIRE(dictionary.size() == 1);
			REQUIRE(dictionary[source] == translations);
		}

		SECTION("adding several translations at once works correctly")
		{
			Dictionary dictionary;
			std::string const source = "cat";
			std::string const translationsString = "кот, кошка";
			std::set<std::string> const translations = { "кот", "кошка" };
			AddTranslations(dictionary, source, translationsString);

			REQUIRE(dictionary.size() == 1);
			REQUIRE(dictionary[source] == translations);
		}

		SECTION("adding translations to the existing word works correctly")
		{
			Dictionary dictionary;
			std::string const source = "cat";
			std::set<std::string> const translations = { "кот", "кошка" };
			AddTranslations(dictionary, source, "кот");
			AddTranslations(dictionary, source, "кошка");

			REQUIRE(dictionary.size() == 1);
			REQUIRE(dictionary[source] == translations);
		}
	}

	SECTION("looking up an existing source returns its translations")
	{
		Dictionary dictionary;
		std::string const source = "cat";
		std::string const translationsString = "кот, кошка";
		std::set<std::string> const translations = { "кот", "кошка" };
		AddTranslations(dictionary, source, translationsString);
		auto const lookedUp = LookupTranslation(dictionary, source);

		REQUIRE(lookedUp.has_value());
		REQUIRE(lookedUp.value() == translations);
	}

	SECTION("looking up non existing source returns empty translations")
	{
		Dictionary dictionary;
		auto const lookedUp = LookupTranslation(dictionary, "cat");

		REQUIRE(!lookedUp.has_value());
	}

	SECTION("source search works case-insensitively, but translations case is preserved")
	{
		Dictionary dictionary;
		std::string const source = "cat";
		std::string const translationsString = "кот, кошка";
		std::set<std::string> const translations = { "кот", "кошка" };
		AddTranslations(dictionary, source, translationsString);
		auto const lookedUp = LookupTranslation(dictionary, "CaT");

		REQUIRE(lookedUp.has_value());
		REQUIRE(lookedUp == translations);
	}
}

TEST_CASE("user interactions work correctly")
{
	// TODO
}
