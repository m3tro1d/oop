#define CATCH_CONFIG_MAIN
#include "../DictionaryConsoleLib.h"
#include "catch.hpp"

TEST_CASE("general string operations work correctly")
{
	SECTION("getting a string in lower case works correctly")
	{
		SECTION("empty string lowered is an empty nevertheless")
		{
			const std::string input;
			auto const result = ToLower(input);
			REQUIRE(result.empty());
		}

		SECTION("string in all lower case is unchanged")
		{
			const std::string input = "hello";
			auto const result = ToLower(input);
			REQUIRE(result == input);
		}

		SECTION("string with mixed lower and upper case turns to only lower case")
		{
			const std::string input = "HelLo ThErE ";
			auto const result = ToLower(input);
			REQUIRE(result == "hello there ");
		}

		SECTION("string in all upper case turns to only lower case")
		{
			const std::string input = "HELLO MOTHERFUCKING WORLD OLOLO!!";
			auto const result = ToLower(input);
			REQUIRE(result == "hello motherfucking world ololo!!");
		}
	}

	SECTION("string trimming works correctly")
	{
		SECTION("empty string trimmed is empty nevertheless")
		{
			std::string input;
			Trim(input);
			REQUIRE(input.empty());
		}

		SECTION("left-padded whitespaces are deleted")
		{
			std::string input = "   hello";
			Trim(input);
			REQUIRE(input == "hello");
		}

		SECTION("right-padded whitespaces are deleted")
		{
			std::string input = "hello    ";
			Trim(input);
			REQUIRE(input == "hello");
		}

		SECTION("both-sides-padded whitespaces are deleted")
		{
			std::string input = " hello    ";
			Trim(input);
			REQUIRE(input == "hello");
		}
	}

	SECTION("parsing string to set works correctly")
	{
		SECTION("empty string results in an empty set")
		{
			const std::string input;
			auto const result = StringToSet(input, ',');
			REQUIRE(result.empty());
		}

		SECTION("string with one value results in set with one value")
		{
			const std::string input = "one";
			auto const result = StringToSet(input, ',');
			REQUIRE(result.find("one") != result.end());
		}

		SECTION("string with several values results in corresponding set")
		{
			const std::string input = "one,two, three  , four";
			auto const result = StringToSet(input, ',');
			REQUIRE(result.find("one") != result.end());
			REQUIRE(result.find("two") != result.end());
			REQUIRE(result.find("three") != result.end());
			REQUIRE(result.find("four") != result.end());
		}

		SECTION("empty values are not saved")
		{
			const std::string input = "one,,two";
			auto const result = StringToSet(input, ',');
			REQUIRE(result.find("one") != result.end());
			REQUIRE(result.find("two") != result.end());
			REQUIRE(result.size() == 2);
		}
	}

	SECTION("serializing set as string works correctly")
	{
		SECTION("empty set results in an empty string")
		{
			const std::set<std::string> input;
			auto const result = SetToString(input, "");
			REQUIRE(result.empty());
		}

		SECTION("set with one value results in a standalone value without delimiters")
		{
			const std::set<std::string> input{ "one" };
			auto const result = SetToString(input, ", ");
			REQUIRE(result == "one");
		}

		SECTION("set with several values results in separated elements")
		{
			const std::set<std::string> input{ "one", "two" };
			auto const result = SetToString(input, ", ");
			REQUIRE(result == "one, two");
		}
	}
}

TEST_CASE("dictionary manipulations work correctly")
{
	SECTION("looking up translations works correctly")
	{
		SECTION("looking up existing phrase returns its translations")
		{
			Dictionary dictionary;
			const std::string phrase = "cat";
			Translations translations{ "??????" };
			dictionary[phrase] = translations;
			auto const result = LookupTranslation(dictionary, phrase);
			REQUIRE(result.has_value());
			REQUIRE(result.value() == translations);
		}

		SECTION("translation lookup is performed case-insensitively")
		{
			Dictionary dictionary;
			Translations translations{ "??????" };
			dictionary["cat"] = translations;
			auto const result = LookupTranslation(dictionary, "CaT");
			REQUIRE(result.has_value());
			REQUIRE(result.value() == translations);
		}

		SECTION("looking up non-existing phrase returns empty value")
		{
			Dictionary dictionary;
			dictionary["cat"] = { "??????" };
			auto const result = LookupTranslation(dictionary, "dog");
			REQUIRE(!result.has_value());
		}
	}

	SECTION("adding direct translations works correctly")
	{
		SECTION("adding non-existing phrase works correctly")
		{
			Dictionary dictionary;
			const std::string phrase = "cat";
			const Translations translations{ "??????" };
			AddDirectTranslations(dictionary, phrase, translations);
			REQUIRE(dictionary.size() == 1);
			REQUIRE(dictionary[phrase] == translations);
		}

		SECTION("adding existing phrase populates its existing translations")
		{
			Dictionary dictionary;
			const std::string phrase = "cat";
			Translations translations{ "??????" };
			const Translations translations1{ "??????????????????", "??????????????" };
			AddDirectTranslations(dictionary, phrase, translations);
			AddDirectTranslations(dictionary, phrase, translations1);
			translations.insert(translations1.begin(), translations1.end());
			REQUIRE(dictionary.size() == 1);
			REQUIRE(dictionary[phrase] == translations);
		}

		SECTION("phrases are saved in lower case, but translations case is preserved")
		{
			Dictionary dictionary;
			const std::string phrase = "CaT";
			const Translations translations{ "??????", "??????????????" };
			AddDirectTranslations(dictionary, phrase, translations);
			REQUIRE(dictionary["cat"] == translations);
		}
	}

	SECTION("adding reverse translations works correctly")
	{
		SECTION("adding non-existing translations works correctly")
		{
			Dictionary dictionary;
			const std::string phrase = "??????";
			const Translations translations{ "cat", "kitty" };
			AddReverseTranslations(dictionary, translations, phrase);
			REQUIRE(dictionary.size() == 2);
			REQUIRE(dictionary["cat"] == Translations{ phrase });
			REQUIRE(dictionary["kitty"] == Translations{ phrase });
		}

		SECTION("adding existing translations populates their existing phrases")
		{
			Dictionary dictionary;
			const std::string phrase = "??????";
			const std::string phrase1 = "??????????";
			const Translations translations{ "cat" };
			AddReverseTranslations(dictionary, translations, phrase);
			AddReverseTranslations(dictionary, translations, phrase1);
			REQUIRE(dictionary.size() == 1);
			REQUIRE(dictionary["cat"] == Translations{ "??????", "??????????" });
		}

		SECTION("translations are saved in lower case, but phrases case is preserved")
		{
			Dictionary dictionary;
			const std::string phrase = "??????";
			const Translations translations{ "Cat", "Kitty" };
			AddReverseTranslations(dictionary, translations, phrase);
			REQUIRE(dictionary.size() == 2);
			REQUIRE(dictionary["cat"] == Translations{ phrase });
			REQUIRE(dictionary["kitty"] == Translations{ phrase });
		}
	}

	SECTION("general translations adding works correctly")
	{
		SECTION("empty translations string results in an exception")
		{
			Dictionary dictionary;
			REQUIRE_THROWS_AS(AddTranslations(dictionary, "cat", ""), std::invalid_argument);
		}
	}
}

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
			std::stringstream input("the red square\n?????????????? ??????????????\ncat\n??????, ??????????\n");
			Dictionary dictionary;
			ReadDictionaryFile(input, dictionary);
			REQUIRE(dictionary.size() == 2);
			REQUIRE(dictionary["cat"] == Translations{ "??????", "??????????" });
			REQUIRE(dictionary["the red square"] == Translations{ "?????????????? ??????????????" });
		}

		SECTION("parsing doesn't rely on special separators")
		{
			std::stringstream input("cat:\n:??????????????????\n");
			Dictionary dictionary;
			ReadDictionaryFile(input, dictionary);
			REQUIRE(dictionary.size() == 1);
			REQUIRE(dictionary["cat:"] == Translations{ ":??????????????????" });
		}

		SECTION("invalid translation file results in an exception")
		{
			std::stringstream input("\ncat\n");
			Dictionary dictionary;
			REQUIRE_THROWS_AS(ReadDictionaryFile(input, dictionary), std::invalid_argument);

			input.str("cat\n\n");
			REQUIRE_THROWS_AS(ReadDictionaryFile(input, dictionary), std::invalid_argument);
		}
	}

	SECTION("dictionary file saving works correctly")
	{
		SECTION("saving empty dictionary results in an empty file")
		{
			Dictionary dictionary;
			std::stringstream output;
			WriteDictionaryFile(output, dictionary);
			REQUIRE(output.str().empty());
		}

		SECTION("saving dictionary with one-to-one values results in populated file")
		{
			Dictionary dictionary;
			dictionary["cat"] = { "??????" };
			std::stringstream output;
			WriteDictionaryFile(output, dictionary);
			REQUIRE(output.str() == "cat\n??????\n");
		}

		SECTION("saving dictionary with values results in populated file")
		{
			Dictionary dictionary;
			dictionary["cat"] = { "??????", "??????????????" };
			std::stringstream output;
			WriteDictionaryFile(output, dictionary);
			REQUIRE(output.str() == "cat\n??????, ??????????????\n");
		}
	}
}

TEST_CASE("user interactions work correctly")
{
	SECTION("prompting for new word works correctly")
	{
		SECTION("empty user input discards new word addition")
		{
			Dictionary dictionary;
			std::stringstream input;
			std::stringstream output;
			const std::string source = "cat";
			REQUIRE(!PromptForNewWord(input, output, dictionary, source));
			REQUIRE(dictionary.empty());
			REQUIRE(output.str() == "Unknown word 'cat'. Enter translation or empty string to abort.\n> "
									"Word 'cat' ignored. Good riddance.\n");
		}

		SECTION("empty user input discards new word addition")
		{
			Dictionary dictionary;
			std::stringstream input("??????\n");
			std::stringstream output;
			const std::string source = "cat";
			REQUIRE(PromptForNewWord(input, output, dictionary, source));
			REQUIRE(dictionary.size() == 2);
			REQUIRE(output.str() == "Unknown word 'cat'. Enter translation or empty string to abort.\n> "
									"Word 'cat' saved in the dictionary as '??????'.\n");
		}
	}
}
