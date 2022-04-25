add_executable(StringStackTest
               StringStack.test.cpp)
target_link_libraries(StringStackTest PUBLIC StringStack catch2)
add_test(NAME StringStackTest COMMAND StringStackTest)
