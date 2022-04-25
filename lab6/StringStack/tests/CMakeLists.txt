add_executable(StringStackTest
               ../CStringStack.h
               ../CStringStack.cpp
               StringStack.test.cpp)
target_link_libraries(StringStackTest PUBLIC catch2)
add_test(NAME StringStackTest COMMAND StringStackTest)
