add_executable(URLParserLibTest
               ../URLParserLib.h
               ../URLParserLib.cpp
               URLParserLib.test.cpp)
target_link_libraries(URLParserLibTest PUBLIC catch2)
add_test(NAME URLParserLibTest COMMAND URLParserLibTest)
