#define CATCH_CONFIG_MAIN
#include "../DictionaryLib.h"
#include "catch.hpp"

TEST_CASE("dictionary file operations work correctly")
{
	SECTION("dictionary file path is determined correctly")
	{
		SECTION("dictionary file path grabs value from the arguments if they are present")
		{
			// TODO
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
		// TODO
	}

	SECTION("dictionary file saving works correctly")
	{
		// TODO
	}
}
