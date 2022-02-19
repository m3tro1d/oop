add_executable(HTMLProcessorTest
               ../HTMLProcessor.h
               ../HTMLProcessor.cpp
               HTMLProcessorTest.cpp)
target_link_libraries(HTMLProcessorTest PUBLIC catch2)
add_test(NAME HTMLProcessorTest COMMAND HTMLProcessorTest)
