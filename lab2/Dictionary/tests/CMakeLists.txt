add_executable(DictionaryTest
               ../DictionaryLib.h
               ../DictionaryLib.cpp
               ../DictionaryFileLib.h
               ../DictionaryFileLib.cpp
               ../DictionaryConsoleLib.h
               ../DictionaryConsoleLib.cpp
               Dictionary.test.cpp)
target_link_libraries(DictionaryTest PUBLIC catch2)
add_test(NAME DictionaryTest COMMAND DictionaryTest)
