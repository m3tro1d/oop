add_executable(DictionaryLibTest
               ../DictionaryLib.h
               ../DictionaryLib.cpp
               DictionaryLibTest.cpp)
target_link_libraries(DictionaryLibTest PUBLIC catch2)
add_test(NAME DictionaryLibTest COMMAND DictionaryLibTest)
